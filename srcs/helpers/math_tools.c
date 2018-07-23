/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:07 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/05/22 11:46:07 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		vector_norm(t_vector vector)
{
	double		norm;

	norm = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
	return (norm);
}

double		dot_product(t_vector vect_1, t_vector vect_2)
{
	double		product;

	product = (vect_1.x * vect_2.x) +
				(vect_1.y * vect_2.y) +
				(vect_1.z * vect_2.z);
	return (product);
}

t_vector	cross_product(t_vector vect_1, t_vector vect_2)
{
	t_vector	product;

	product.x = vect_1.y * vect_2.z - vect_2.y * vect_1.z;
	product.y = vect_1.z * vect_2.x - vect_2.z * vect_1.x;
	product.z = vect_1.x * vect_2.y - vect_2.x * vect_1.y;
	return (product);
}

t_vector	normalize_vector(t_vector vector)
{
	double		norm;

	norm = vector_norm(vector);
	vector.x /= norm;
	vector.y /= norm;
	vector.z /= norm;
	return (vector);
}

double		points_norm(t_point p1, t_point p2)
{
	double		distance;

	distance= sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) +
			pow(p2.z - p1.z, 2));
	return (distance);
}

double		degrees_to_radian(int degrees)
{
	double	radian;

	radian = ((double)degrees * M_PI) / 180;
	return (radian);
}

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
