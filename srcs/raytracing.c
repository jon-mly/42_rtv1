#include "rtv1.h"

static t_ray		init_ray(int x, int y, t_camera camera)
{
	t_ray		ray;

	ray.origin.x = camera.up_left_corner.x + (double)x * camera.horizontal_step;
	ray.origin.y = camera.up_left_corner.y - (double)y * camera.vertical_step;
	ray.origin.z = camera.position.z;
	ray.direction.x = ray.origin.x - camera.spot.x;
	ray.direction.y = ray.origin.y - camera.spot.y;
	ray.direction.z = ray.origin.z - camera.spot.z;
	ray.direction = normalize_vector(ray.direction);
	ray.intersect = FALSE;
	return (ray);
}

/*
** The function tries to find the closest intersection between the ray and
** each of the objects in the scene.
*/

void				pixel_raytracing(int x, int y, t_env *env)
{
	t_ray		ray;
	t_object	object;
	int			object_index;

	ray = init_ray(x, y, env->camera);
	object_index = -1;
	while (++object_index < env->scene.objects_count)
	{
		object = env->scene.objects[object_index];
		if (object.type == SPHERE)
			ray = sphere_intersection(ray, *((t_sphere*)(object.object)));
	}
	ft_putendl(ray.intersect ? "Should print" : "No intersect");
	if (ray.intersect)
		fill_pixel(env, x, y, color(255, 255, 255, 255));
}
