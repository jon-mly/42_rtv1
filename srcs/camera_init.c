#include "rtv1.h"

t_camera	init_camera(t_env *env)
{
	t_camera	camera;

	camera.position = vector(-0.4, 0.3, 0);
	camera.direction = vector(0, 0, 1);
	camera.spot = point(0, 0, -1.0);
	camera.width = 0.8;
	camera.height = 0.6;
	camera.plane_dist = 1.0;
	camera.up_left_corner = camera.position;
	camera.horizontal_step = camera.width / (double)(env->win_width);
	camera.vertical_step = camera.height / (double)(env->win_height);
	return (camera);
}
