#include "rtv1.h"

/*
** Initialize the ray with the coordinates of the camera (both position and
ri
** directional vector).
*/

static t_ray		init_ray(int x, int y, t_camera camera)
{
	t_ray		ray;
	t_point		projector_point;

	projector_point.x = camera.up_left_corner.x + (double)x * camera.horizontal_step;
	projector_point.y = camera.up_left_corner.y - (double)y * camera.vertical_step;
	projector_point.z = camera.position.z;
	ray.direction = vector_points(camera.spot, projector_point);
	ray.direction = normalize_vector(ray.direction);
	ray.origin = camera.spot;
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
		ray.intersection.x = ray.origin.x + ray.direction.x * closest_distance;
		ray.intersection.y = ray.origin.y + ray.direction.y * closest_distance;
		ray.intersection.z = ray.origin.z + ray.direction.z * closest_distance;
		fill_pixel(env, x, y, get_color_on_intersection(ray, closest_object,
			env));
	}
	else
		fill_pixel(env, x, y, color(0, 0, 0, 0));// TODO: apply diffuse color
}
