#include "rtv1.h"

static t_ray	init_light_ray(t_light light, t_ray ray)
{
	t_ray		light_ray;
	t_vector	direction;

	light_ray.origin = light.position;
	direction = vector_points(light_ray.origin, ray.intersection);
	light_ray.direction = normalize_vector(direction);
	light_ray.intersect = FALSE;
	light_ray.color = color(0, 0, 0, 0);
	return (light_ray);
}

static t_ray	intersect_with_object(t_ray light_ray, t_object object)
{
	light_ray = intersect_object(light_ray, object);
	return (light_ray);
}

static t_color	light_for_intersection(t_ray light_ray, t_ray ray, t_object
	object, t_light light)
{
	t_vector	normal;
	double		cosinus;
	t_color		color;

	normal = shape_normal(ray, object);
	ft_putendl("did get normal");
	cosinus = dot_product(light_ray.direction, normal);
	if (cosinus <= 0)
		return (light_ray.color);
	color.r = (int)(fmin((double)object.color.r + cosinus * (double)light.color.r, 255));
	color.g = (int)(fmin((double)object.color.g + cosinus * (double)light.color.g, 255));
	color.b = (int)(fmin((double)object.color.b + cosinus * (double)light.color.b, 255));
	return (color);
}

t_color			get_color_on_intersection(t_ray ray, t_object *closest_object,
	t_env *env)
{
	t_ray		light_ray;
	int			light_index;
	int			object_index;
	t_light		light;
	t_object	object;

	light_index = -1;
	while (++light_index < env->scene.lights_count)
	{
		light = env->scene.lights[light_index];
		light_ray = init_light_ray(light, ray);
		object_index = -1;
		ray.color = light_for_intersection(light_ray, ray, object, light);
		while (++object_index < env->scene.objects_count)
		{
			object = env->scene.objects[object_index];
			if (&object != closest_object && (light_ray =
				intersect_object(light_ray, object)).intersect == FALSE)
				ray.color = light_for_intersection(light_ray, ray, object, light);
		}
	}
	return (ray.color);
}
