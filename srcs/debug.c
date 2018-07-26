#include "rtv1.h"

static t_ray	debug_init_light_ray(t_light light, t_ray ray, t_object object)
{
	t_ray		light_ray;
	t_vector	direction;

	light_ray.origin = light.position;
	direction = vector_points(light_ray.origin, ray.intersection);
	light_ray.norm = vector_norm(direction);
	light_ray.direction = normalize_vector(direction);
	light_ray.intersect = FALSE;
	light_ray.color = color(object.color.r / 4, object.color.g / 4, object.color.b / 4, 0);
	return (light_ray);
}

static t_color	debug_light_for_intersection(t_ray light_ray, t_ray ray, t_object
	object, t_light light)
{
	t_vector	normal;
	float		cosinus;
	t_color		color;

	normal = shape_normal(ray, object);
	cosinus = dot_product(light_ray.direction, normal);
	// if angle is higher than +/-PI/2, the point is shadowed whatsoever.
	printf("cosinus = %.2f\n", cosinus);
	if (cosinus >= 0)
	{
		printf("Returned for cosinus higher than 0.\n");
		return (light_ray.color);
	}
	color.r = (int)(fmax(fmin((double)object.color.r / (3) - cosinus * (double)light.color.r / 2, 255), 0));
	color.g = (int)(fmax(fmin((double)object.color.g / (3) - cosinus * (double)light.color.g / 2, 255), 0));
	color.b = (int)(fmax(fmin((double)object.color.b / (3) - cosinus * (double)light.color.b / 2, 255), 0));
	color.a = 0;
	return (color);
}

static t_color			debug_get_color_on_intersection(t_ray ray, t_object *closest_object,
	t_env *env)
{
	t_ray		light_ray;
	int			light_index;
	int			object_index;
	float		norm;
	t_color		coloration;

	light_index = -1;
	coloration = closest_object->color;
	while (++light_index < env->scene.lights_count)
	{
		light_ray = debug_init_light_ray(env->scene.lights[light_index], ray,
				*closest_object);
		norm = light_ray.norm;
		coloration = debug_light_for_intersection(light_ray, ray, *closest_object,
				env->scene.lights[light_index]);
		object_index = -1;
		while (++object_index < env->scene.objects_count)
		{
			if (&(env->scene.objects[object_index]) != closest_object)
			{
				light_ray = intersect_object(light_ray,
						env->scene.objects[object_index]);
				if (light_ray.intersect && light_ray.norm < norm &&
						light_ray.norm > 0)
				{
					printf("Shadowed because of closer object : %s\n", env->scene.objects[object_index].name);
					return (light_ray.color);
				}
			}
		}
	}
	printf("Point of object is directly exposed to light source\n");
	return (coloration);
}

void	debug_raytracing(int x, int y, t_env *env)
{
	t_ray		ray;
	int			object_index;
	t_object	*closest_object;
	float		closest_distance;

	ray = init_ray(x, y, env->camera);
	closest_object = NULL;
	object_index = -1;
	while (++object_index < env->scene.objects_count)
	{
		ray = intersect_object(ray, env->scene.objects[object_index]);
		if (ray.intersect && ((closest_object != NULL && ray.norm < closest_distance) || closest_object == NULL) && ray.norm > 0)
		{
			closest_object = &(env->scene.objects[object_index]);
			closest_distance = ray.norm;
		}
	}
	if (closest_object != NULL)
	{
		ray.norm = closest_distance;
		ray.intersection.x = ray.origin.x + ray.direction.x * closest_distance;
		ray.intersection.y = ray.origin.y + ray.direction.y * closest_distance;
		ray.intersection.z = ray.origin.z + ray.direction.z * closest_distance;
		printf("Closest object at %.2f, named %s\n", ray.norm, closest_object->name);
		debug_get_color_on_intersection(ray, closest_object, env);
	}
}

int		debug_mouse_event(int event, int x, int y, void *param)
{
	t_env *env;

	env = (t_env*)param;
	if (event != 1)
		return 0;
	debug_raytracing(x, y, env);
	return 0;
}
