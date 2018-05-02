#include "rtv1.h"

static t_ray	init_light_ray(t_light light, t_ray ray)
{
	t_ray		light_ray;
	t_vector	direction;

	direction.x = ray.origin.x + ray.direction.x * norm - light_ray.origin.x;
	direction.y = ray.origin.y + ray.direction.y * norm - light_ray.origin.y;
	direction.x = ray.origin.z + ray.direction.z * norm - light_ray.origin.z;
	light_ray.origin = light.position;
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
	object)
{
	t_vector	normal;
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
		while (++object_index < env->scene.objects_count)
		{
			object = env->scene.objects[object_index]
			if (&object != closest_object && (light_ray =
				intersect_object(light_ray, object)).intersect == FALSE)
				
		}
	}
	return (ray.color);
}
