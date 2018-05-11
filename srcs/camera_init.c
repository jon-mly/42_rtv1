#include "rtv1.h"

t_camera	init_camera(t_env *env)
{
	t_camera	camera;

	camera.width = 1.2;
	camera.height = 0.8;
	camera.plane_dist = 0.5;
	camera.spot = point(0, 7, -30);
	camera.direction = normalize_vector(vector(0, 0, 1));
	camera.position = vector(camera.spot.x + camera.direction.x - camera.width / 2,
			camera.spot.y + camera.direction.y + camera.height / 2,
			camera.spot.z + camera.direction.z + camera.plane_dist);
	camera.up_left_corner = camera.position;
	camera.horizontal_step = camera.width / (double)(env->win_width);
	camera.vertical_step = camera.height / (double)(env->win_height);
	return (camera);
}
