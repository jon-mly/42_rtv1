/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:14 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/05/22 11:46:15 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// UNUSED

t_vector	rotate_cone_angles(t_cone cone, t_vector vect,
			int reverse)
{
	if (!reverse)
	{
		vect = vect_rotate_y(vect, -cone.y_angle);
		vect = vect_rotate_x(vect, -cone.x_angle);
	}
	else
	{
		vect = vect_rotate_y(vect, cone.y_angle);
		vect = vect_rotate_x(vect, cone.x_angle);
	}
	return (vect);
}


/*
** Calculate the norm of the ray from the origin of it to the intersection
** with the cylinder given in parameter.
** Returns the ray with "intersect" and "norm" values set up
*/

t_ray		cone_intersection(t_ray ray, t_cone cone)
{
	t_vector	distance;
	t_vector	ray_dir;
	double		a;
	double		b;
	double		c;
	double		k;
	double		discriminant;

	distance = vector_points(cone.center, ray.origin);
	ray_dir = rotate_cone_angles(cone, ray.direction, 0);
	distance = rotate_cone_angles(cone, distance, 0);
	k = -1 - pow(tan(cone.angle), 2);
	a = pow(vector_norm(ray_dir), 2) + k * pow(ray_dir.z, 2);
	b = 2 * (dot_product(distance, ray_dir) + k * ray_dir.z * distance.z);
	c = pow(vector_norm(distance), 2) + k * pow(distance.z, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		ray.intersect = FALSE;
	else
	{
		ray.intersect = TRUE;
		ray.norm = (fmin((-b - sqrt(discriminant)) / (2 * a),
					(-b + sqrt(discriminant) / (2 * a))));
	}
	return (ray);
}
