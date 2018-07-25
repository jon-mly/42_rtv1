/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:18 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/07/25 16:04:16 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	ray.norm = closest_distance_quadratic(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}

/*
t_vector		cylinder_normal(t_ray ray, t_cylinder cylinder)
{
	t_vector	normal;
	t_point		pt_normal;
	t_point		pt_normal_bis;
	double		dist_normal;

	dist_normal = sqrt(pow(points_norm(ray.intersection, cylinder.point), 2) -
			pow(cylinder.radius, 2));
	pt_normal.x = cylinder.point.x + dist_normal * cylinder.direction.x;
	pt_normal.y = cylinder.point.y + dist_normal * cylinder.direction.y;
	pt_normal.z = cylinder.point.z + dist_normal * cylinder.direction.z;
	pt_normal_bis.x = cylinder.point.x - dist_normal * cylinder.direction.x;
	pt_normal_bis.y = cylinder.point.y - dist_normal * cylinder.direction.y;
	pt_normal_bis.z = cylinder.point.z - dist_normal * cylinder.direction.z;
	if (points_norm(ray.intersection, pt_normal) > points_norm(ray.intersection,
				pt_normal_bis))
		pt_normal = pt_normal_bis;
	normal = vector_points(pt_normal, ray.intersection);
	return (normalize_vector(normal));
}
*/

t_vector		cylinder_normal(t_ray ray, t_cylinder cylinder)
{
	t_vector	distance;
//	double		normal_distance;
	t_point		normal_point;
	t_vector	normal;

	distance = vector_points(cylinder.point, ray.intersection);
	distance = rotate_cylinder_angles(cylinder, distance, 0);
//	printf("distance %.2f, %.2f, %.2f\n", distance.x, distance.y, distance.z);
//	normal_distance = sqrt(pow(vector_norm(distance), 2) - pow(cylinder.radius, 2));
	normal_point.x = 0;
	normal_point.y = 0;
	normal_point.z = distance.z;
//	if (points_norm(normal_point, distance) > cylinder.radius)
//		normal_point.z -= 2 * normal_distance;
	normal = vector_points(normal_point, distance);
//	printf("norm = %.2f, z_coord = %.2f\n", vector_norm(normal), normal.z);
	normal = rotate_cylinder_angles(cylinder, distance, 1);
	return (normalize_vector(normal));
}
