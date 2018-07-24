#include "rtv1.h"

void	debug_raytracing(int x, int y, t_env *env)
{
	t_ray		ray;
	int			object_index;
	t_object	*closest_object;
	double		closest_distance;

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
