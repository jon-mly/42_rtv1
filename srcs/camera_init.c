#include "rtv1.h"

t_camera	init_camera(t_env *env)
{
	t_camera	camera;

	camera.width = 1.2;
	camera.height = 0.8;
	camera.plane_dist = 0.5;
	camera.spot = point(0, 0, -1.0);
	camera.position = vector(-camera.width / 2, camera.height / 2, camera.spot.z + camera.plane_dist);
	camera.direction = vector(0, 0, 0);
	camera.up_left_corner = camera.position;
	camera.horizontal_step = camera.width / (double)(env->win_width);
	camera.vertical_step = camera.height / (double)(env->win_height);
	return (camera);
}
