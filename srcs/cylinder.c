/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:18 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/07/23 16:27:46 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// UNUSED


/*
** Ref is supposed to be (0,0,1) in the new referential.
** - lat : lattitude of the reference, Oz rotation
** - lon : longitude of the reference, Oy rotation.
** - projected_ref : copy of ref with a coordinate nulled (projection on a
** given axis)
** - unit : unit vector, either (1,0,0)
*/

t_vector	rotate_cylinder_angles(t_cylinder cylinder, t_vector vect,
			int reverse)
{
	if (!reverse)
	{
		vect = vect_rotate_y(vect, -cylinder.y_angle);
		vect = vect_rotate_x(vect, -cylinder.x_angle);
	}
	else
	{
		vect = vect_rotate_y(vect, cylinder.y_angle);
		vect = vect_rotate_x(vect, cylinder.x_angle);
	}
	return (vect);
}

/*
** Calculate the norm of the ray from the origin of it to the intersection
** with the cylinder given in parameter.
** Returns the ray with "intersect" and "norm" values set up
*/

t_ray		cylinder_intersection(t_ray ray, t_cylinder cylinder)
{
	t_vector	distance;
	t_vector	ray_dir;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	distance = vector_points(cylinder.point, ray.origin);
	ray_dir = rotate_cylinder_angles(cylinder, ray.direction, 0);
	distance = rotate_cylinder_angles(cylinder, distance, 0);
	a = pow(ray_dir.x, 2) + pow(ray_dir.y, 2);
	b = 2 * (distance.x * ray_dir.x + distance.y * ray_dir.y);
	c = pow(distance.x, 2) + pow(distance.y, 2) - pow(cylinder.radius, 2);
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
