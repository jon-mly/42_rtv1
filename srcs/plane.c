/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:51 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/05/22 11:46:52 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Calculate the norm of the ray from the origin of it to the intersection
** with the plane given in parameter.
** Returns the ray with "intersect" and "norm" values set up
*/

t_ray		plane_intersection(t_ray ray, t_plane plane)
{
	t_vector		distance;
	double			norm;

	distance = vector_points(plane.point, ray.origin);
	norm = dot_product(plane.normal, plane.point) - dot_product(plane.normal,
		ray.origin) / dot_product(plane.normal, ray.direction);
	if (norm < 0.0001 || norm > 1000)
		ray.intersect = FALSE;
	else
	{
		ray.intersect = TRUE;
		ray.norm = norm;
	}
	return (ray);
}
