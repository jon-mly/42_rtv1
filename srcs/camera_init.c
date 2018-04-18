#include "rtv1.h"

static t_vector		get_position(void)
{
	t_vector	position;

	position.z = 0;
	position.x = -0.3;
	position.y = 0;
	return (position);
}

static t_vector		get_direction(void)
{
	t_vector	direction;

	direction.x = 0;
	direction.y = 1;
	direction.z = 0;
	return (direction);
}

t_camera	init_camera(t_env *env)
{
	t_camera	camera;

	camera.position = get_position();
	camera.direction = get_direction();
	camera.width = 0.6;
	camera.height = 0.45;
	camera.plane_dist = 1.0;
	camera.horizontal_step = camera.width / (double)(env->win_width);
	camera.vertical_step = camera.height / (double)(env->win_height);
	return (camera);
}
