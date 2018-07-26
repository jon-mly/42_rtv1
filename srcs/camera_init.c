/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:10 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/07/23 13:26:37 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** TODO: read camera position from a file
*/

t_camera	init_camera(t_env *env)
{
	t_camera	camera;

	camera.width = 1.5;
	camera.height = 1;
	camera.plane_dist = 0.2;
	camera.spot = point(0, 12, -60);
	camera.direction = normalize_vector(vector(0, 0, 1));
	camera.position = vector(camera.spot.x + camera.direction.x - camera.width / 2,
			camera.spot.y + camera.direction.y + camera.height / 2,
			camera.spot.z + camera.direction.z);
	camera.up_left_corner = camera.position;
	camera.horizontal_step = camera.width / (double)(env->win_width);
	camera.vertical_step = camera.height / (double)(env->win_height);
	return (camera);
}
