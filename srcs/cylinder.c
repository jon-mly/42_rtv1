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

t_vector	vect_rotate_x(t_vector vector, double angle)
{
	t_vector	rotated;

	rotated.x = vector.x;
	rotated.y = vector.y * cos(angle) + vector.z * sin(angle);
	rotated.z = -vector.y * sin(angle) + vector.z * cos(angle);
	return (rotated);
}

t_vector	vect_rotate_z(t_vector vector, double angle)
{
	t_vector	rotated;

	rotated.x = vector.x * cos(angle) + vector.y * sin(angle);
	rotated.y = -vector.x * sin(angle) + vector.y * cos(angle);
	rotated.z = vector.z;
	return (rotated);
}

t_vector	vect_rotate_y(t_vector vector, double angle)
{
	t_vector	rotated;

	rotated.x = vector.x * cos(angle) - vector.z * sin(angle);
	rotated.y = vector.y;
	rotated.z = vector.x * sin(angle) + vector.z * cos(angle);
	return (rotated);
}

/*
** Ref is supposed to be (0,0,1) in the new referential.
** - lat : lattitude of the reference, Oz rotation
** - lon : longitude of the reference, Oy rotation.
** - projected_ref : copy of ref with a coordinate nulled (projection on a
** given axis)
** - unit : unit vector, either (1,0,0)
*/

t_vector	apply_rotation(t_vector ref, t_vector vect, int reverse)
{
	double		lat;
	double		lon;
	t_vector	projected_ref;
	t_vector	unit;

	unit = vector(0, 0, 1);
	// Rotation around Ox, along Oz.
	projected_ref = ref;
	projected_ref.z = 0;
	lat = (vector_norm(projected_ref) > 0) ? acos(dot_product(projected_ref, unit) / vector_norm(projected_ref)) : 0;
	// Rotation around Oy, along Oz.
	projected_ref = ref;
	projected_ref.y = 0;
	lon = (vector_norm(projected_ref) > 0) ? acos(dot_product(projected_ref, unit) / vector_norm(projected_ref)) : 0;
	if (!reverse)
	{
		vect = vect_rotate_z(vect, -lat);
		vect = vect_rotate_y(vect, -lon);
	}
	else
	{
		vect = vect_rotate_z(vect, lat);
		vect = vect_rotate_y(vect, lon);
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
	t_vector	cyl_dir;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	distance = vector_points(ray.origin, cylinder.point);
	ray_dir = apply_rotation(cylinder.direction, ray.direction, 0);
	distance = apply_rotation(cylinder.direction, distance, 0);
	cyl_dir = apply_rotation(cylinder.direction, cylinder.direction, 0);
	a = pow(ray_dir.x, 2) + pow(ray_dir.y, 2) ;
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
