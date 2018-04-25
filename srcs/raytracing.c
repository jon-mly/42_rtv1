#include "rtv1.h"

static t_ray		init_ray(int x, int y, t_camera camera)
{
	t_ray		ray;
	t_point		projector_point;

	projector_point.x = camera.up_left_corner.x + (double)x * camera.horizontal_step;
	projector_point.y = camera.up_left_corner.y - (double)y * camera.vertical_step;
	projector_point.z = camera.position.z;
//	printf("origin x:%.2f, y:%.2f, z:%.2f\n", ray.origin.x, ray.origin.y, ray.origin.z);
	ray.direction = vector_points(camera.spot, projector_point);
	ray.direction = normalize_vector(ray.direction);
	ray.origin = camera.spot;
//	printf("direction x=%.2f, y=%.2f, z=%.2f\n", ray.direction.x, ray.direction.y, ray.direction.z);
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
	if (ray.intersect)
		fill_pixel(env, x, y, color(150, 150, 150, 0));
}
