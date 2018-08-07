/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:54 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/05/31 17:32:37 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Initialize the ray with the coordinates of the camera (both position and
ri
** directional vector).
*/

t_ray		init_ray(int x, int y, t_camera camera)
{
	t_ray		ray;
	t_point		projector_point;

	projector_point.x = camera.up_left_corner.x + (double)x * camera.horizontal_vect.x + (double)y * camera.vertical_vect.x;
	projector_point.y = camera.up_left_corner.y + (double)x * camera.horizontal_vect.y + (double)y * camera.vertical_vect.y;
	projector_point.z = camera.up_left_corner.z + (double)x * camera.horizontal_vect.z + (double)y * camera.vertical_vect.z;
	ray.direction = vector_points(camera.spot, projector_point);
	ray.direction = normalize_vector(ray.direction);
	ray.origin = camera.spot;
	ray.intersect = FALSE;
	return (ray);
}

/*
** The function tries to find the closest intersection between the ray and
** each of the objects in the scene. To do so, it tracks the closest distance
** calculated so far and compares (+ replaces) it to a new distance if there
** is an intersection.
** If an intersection has been found, the color that should be applied on
** the given pixel is calculated (cf. lighting.c) and applied.
*/

void				pixel_raytracing(int x, int y, t_env *env)
{
	t_ray		ray;
	int			object_index;
	t_object	*closest_object;
	float		closest_distance;

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
		ray.norm = closest_distance;
		ray.intersection.x = ray.origin.x + ray.direction.x * closest_distance;
		ray.intersection.y = ray.origin.y + ray.direction.y * closest_distance;
		ray.intersection.z = ray.origin.z + ray.direction.z * closest_distance;
		fill_pixel(env, x, y, get_color_on_intersection(ray, closest_object,
			env));
	}
	else
		fill_pixel(env, x, y, color(0, 0, 0, 0));
}
