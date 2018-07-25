/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:14 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/07/25 17:17:55 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
//	double		discriminant;

	distance = vector_points(cone.center, ray.origin);
	ray_dir = rotate_cone_angles(cone, ray.direction, 0);
	distance = rotate_cone_angles(cone, distance, 0);
	k = -1 - pow(tan(cone.angle), 2);
	a = pow(vector_norm(ray_dir), 2) + k * pow(ray_dir.z, 2);
	b = 2 * (dot_product(distance, ray_dir) + k * ray_dir.z * distance.z);
	c = pow(vector_norm(distance), 2) + k * pow(distance.z, 2);
	ray.norm = closest_distance_quadratic(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}

t_vector		cone_normal(t_ray ray, t_cone cone)
{
	t_vector	normal;
	t_point		pt_dir;
	t_point		pt_dir_bis;
	t_point		pt_normal;
	double		distance;

	distance = cos(cone.angle) * points_norm(ray.intersection, cone.center);
	pt_dir.x = cone.center.x + distance * cone.direction.x;
	pt_dir.y = cone.center.y + distance * cone.direction.y;
	pt_dir.z = cone.center.z + distance * cone.direction.z;
	pt_dir_bis.x = cone.center.x - distance * cone.direction.x;
	pt_dir_bis.y = cone.center.y - distance * cone.direction.y;
	pt_dir_bis.z = cone.center.z - distance * cone.direction.z;
	if (points_norm(ray.intersection, pt_dir) > points_norm(ray.intersection,
				pt_dir_bis))
		pt_dir = pt_dir_bis;
	distance = points_norm(pt_dir, ray.intersection) * tan(cone.angle);
	pt_normal.x = pt_dir.x + distance * ray.direction.x;
	pt_normal.y = pt_dir.y + distance * ray.direction.y;
	pt_normal.z = pt_dir.z + distance * ray.direction.z;
	normal = vector_points(pt_normal, ray.intersection);
	return (normalize_vector(normal));
}

/*
t_vector		cone_normal(t_ray ray, t_cone cone)
{
	t_vector	distance;
	double		normal_dist;
	double		variated_dist;
	t_point		normal_point;
	t_point		normal_point_2;
	t_vector	normal;

	distance = vector_points(cone.center, ray.intersection);
	distance = rotate_cone_angles(cone, distance, 0);
	normal_dist = sqrt(1 - pow(sin(cone.angle), 2)) * vector_norm(distance);
	variated_dist = tan(cone.angle) * sin(cone.angle) * vector_norm(distance);
	normal_point = (t_point){0, 0, normal_dist + variated_dist};
	normal_point_2 = (t_point){0, 0, -normal_dist - variated_dist};
	if (points_norm(normal_point, ray.intersection) > points_norm(normal_point_2, ray.intersection))
		normal_point = normal_point_2;
	normal = vector_points(normal_point, ray.intersection);
	normal = rotate_cone_angles(cone, normal, 1);
	return (normalize_vector(normal));
}
*/
