#include "rtv1.h"

static t_vector 		rotate_for_angles(t_vector vect, t_camera camera)
{
	vect = vect_rotate_x(vect, camera.x_angle, 0);
	vect = vect_rotate_y(vect, camera.y_angle, 0);
	return (vect);
}

static t_camera			get_default_camera_parameters(t_env *env)
{
	t_camera	camera;

	camera.width = 3;
	camera.height = 2;
	camera.plane_dist = 0.8;
	camera.spot = point(0, 0, 0);
	camera.direction = normalize_vector(vector(0, 0, 1));
	camera.position = vector(-camera.width / 2, camera.height / 2, camera.plane_dist);
	camera.horizontal_vect = vector(camera.width / (double)(env->win_width), 0, 0);
	camera.vertical_vect = vector(0, -camera.height / (double)(env->win_height), 0);
	return (camera);
}

static t_camera			convert_camera_vector(t_camera camera)
{
	camera.horizontal_vect = rotate_for_angles(camera.horizontal_vect, camera);
	camera.vertical_vect = rotate_for_angles(camera.vertical_vect, camera);
	camera.direction = rotate_for_angles(camera.direction, camera);
	camera.position = rotate_for_angles(camera.position, camera);
	camera.up_left_corner = 
		point(camera.spot.x + camera.position.x,
		camera.spot.y + camera.position.y,
		camera.spot.z + camera.position.z);
	return (camera);
}

/*
** camera
** required structure
**
** camera {
** position [x] [y] [z]
** angles [pitch] [yaw]
** }
*/

t_camera		set_camera(int fd, t_env *env)
{
	t_camera	camera;
	char		**line;

	camera = get_default_camera_parameters(env);
	while ((line = split_new_line(fd)) && ft_strequ(line[0], "}") == FALSE)
	{
		if (line_len(line) == 4 && ft_strequ(line[0], "position"))
			camera.spot = point(ft_atoi(line[1]), ft_atoi(line[2]),
				ft_atoi(line[3]));
		else if (line_len(line) == 3 && ft_strequ(line[0], "angles"))
		{
			camera.x_angle = degrees_to_radian(ft_atoi(line[1]));
			camera.y_angle = degrees_to_radian(ft_atoi(line[2]));
		}
	}
	camera = convert_camera_vector(camera);
	printf("Camera position : %.2f, %.2f, %.2f\n", camera.spot.x, camera.spot.y, camera.spot.z);
	printf("Camera direction : %.2f, %.2f, %.2f\n", camera.direction.x, camera.direction.y, camera.direction.z);
	printf("Camera horizontal vect : %.5f, %.5f, %.5f\n", camera.horizontal_vect.x, camera.horizontal_vect.y, camera.horizontal_vect.z);
	printf("Camera vertical vect : %.5f, %.5f, %.5f\n", camera.vertical_vect.x, camera.vertical_vect.y, camera.vertical_vect.z);
	printf("Camera position : %.5f, %.5f, %.5f\n", camera.position.x, camera.position.y, camera.position.z);
	printf("Camera up left corner : %.2f, %.2f, %.2f\n", camera.up_left_corner.x, camera.up_left_corner.y, camera.up_left_corner.z);
	return (camera);
}
