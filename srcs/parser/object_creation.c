/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 16:09:07 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/09/07 11:50:40 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** sphere
** required structure
**
** sphere {
** radius [radius]
** center [x] [y] [z]
** color [r] [g] [b]
** }
*/

static t_object		add_new_sphere(int fd)
{
	t_object	sphere;

	sphere.typpe = SPHERE;
	sphere.radius = 1;
	sphere.center = point(10, 12, 6);
	sphere.color = color(255, 255, 255, 0);
	sphere = parse_object(fd, &sphere);
	sphere.name = "Sphere";
	return (sphere);
}

/*
** plane
** required structure
**
** plane {
** normal [x] [y] [z]
** point [x] [y] [z]
** color [r] [g] [b]
** }
*/

static t_object		add_new_plane(int fd)
{
	char		**line;
	t_object	plane;

	plane.typpe = PLANE;
	plane.normal = normalize_vector(vector(0, 1, 0));
	plane.point = point(0, 0, 0);
	plane.color = color(255, 255, 255, 0);
	plane = parse_object(fd, &plane);
	plane.name = "Plane";
	return (plane);
}

/*
** cone
** required structure
**
** cone {
** pi_divider [PI / x . x value expected]
** direction [x] [y] [z]
** center [x] [y] [z]
** color [r] [g] [b]
** }
*/

static t_object		add_new_cone(int fd)
{
	t_object	cone;

	cone.typpe = CONE;
	cone.angle = M_PI / 6;
	cone.direction = normalize_vector(vector(0, 0, 1));
	cone.center = point(0, 0, 0);
	cone.color = color(255, 255, 255, 0);
	cone.name = "Cone";
	cone = parse_object(fd, &cone);
	cone.direction = rotate_cone_angles(cone, cone.direction, 1);
	return (cone);
}

/*
** cylinder
** required structure
**
** cylinder {
** radius [radius]
** position [x] [y] [z]
** direction [x] [y] [z]
** color [r] [g] [b]
** angles [y_angle / longitude °] [x_angle / latitude °]
** }
*/

static t_object		add_new_cylinder(int fd)
{
	t_object	cylinder;

	cylinder.typpe = CYLINDER;
	cylinder.radius = 1;
	cylinder.direction = normalize_vector(vector(0, 0, 1));
	cylinder.point = point(0, 0, 0);
	cylinder.color = color(255, 255, 255, 0);
	cylinder.name = "Cylinder";
	cylinder = parse_object(fd, &cylinder);
	cylinder.direction = rotate_cylinder_angles(cylinder, cylinder.direction, 1);
	return (cylinder);
}

static t_object		add_new_disc(int fd)
{
	t_object	disc;

	disc.typpe = DISC;
	disc.normal = normalize_vector(vector(0, 1, 0));
	disc.point = point(0, 0, 0);
	disc.color = color(255, 255, 255, 0);
	disc.radius = 10;
	disc = parse_object(fd, &disc);
	disc.name = "Disc";
	return (disc);
}

static t_object		add_new_rectangle(int fd)
{
	t_object	rectangle;

	rectangle.typpe = RECTANGLE;
	rectangle.color = color(255, 255, 255, 0);
	rectangle.x_angle = 0;
	rectangle.y_angle = 0;
	rectangle.normal = vector(0, 1, 0);
	rectangle.width = 0;
	rectangle.height = 0;
	rectangle = parse_object(fd, &rectangle);
	rectangle.name = "Rectangle";
	rectangle.normal = rotate_vector_angles(rectangle, rectangle.normal, 1);
	return (rectangle);
}

static t_object		add_new_triangle(int fd)
{
	t_object	triangle;

	triangle.typpe = TRIANGLE;
	triangle.color = color(255, 255, 255, 0);
	triangle.first_vect = vector(1, 0, 0);
	triangle.second_vect = vector(0, 0, 1);
	triangle.point = point(0, 0, 0);
	triangle = parse_object(fd, &triangle);
	triangle.normal = normalize_vector(cross_product(triangle.first_vect, triangle.second_vect));
	triangle.name = "Triangle";
	return (triangle);
}

static t_object		add_new_parallelogram(int fd)
{
	t_object	parallelogram;

	parallelogram.typpe = PARALLELOGRAM;
	parallelogram.color = color(255, 255, 255, 0);
	parallelogram.first_vect = vector(1, 0, 0);
	parallelogram.second_vect = vector(0, 0, 1);
	parallelogram.point = point(0, 0, 0);
	parallelogram = parse_object(fd, &parallelogram);
	parallelogram.normal = normalize_vector(cross_product(parallelogram.first_vect, parallelogram.second_vect));
	parallelogram.name = "parallelogram";
	return (parallelogram);
}

t_object			add_new_object(int fd, char *type)
{
	if (ft_strequ(type, "cylinder"))
		return (add_new_cylinder(fd));
	else if (ft_strequ(type, "sphere"))
		return (add_new_sphere(fd));
	else if (ft_strequ(type, "plane"))
		return (add_new_plane(fd));
	else if (ft_strequ(type, "disc"))
		return (add_new_disc(fd));
	else if (ft_strequ(type, "rectangle"))
		return add_new_rectangle(fd);
	else if (ft_strequ(type, "triangle"))
		return add_new_triangle(fd);
	else if (ft_strequ(type, "parallelogram"))
		return add_new_parallelogram(fd);
	else
		return (add_new_cone(fd));
}
