#include "rtv1.h"

static void		init_ray(int x, int y, t_camera camera)
{
	t_vector	direction;
	t_point		origin;
	t_ray		ray;

	origin.y = camera.y;
	origin.z = camera.up_left_corner.z - (double)y * camera.vertical_step;
	origin.x = camera.up_left_corner.x + (double)x * camera.horizontal_step;
	ray.origin = origin;
	
}

void			pixel_raytracing(int x, int y, t_env *env)
{
	t_ray		ray;

	ray = init_ray(x, y, env->camera);
}
