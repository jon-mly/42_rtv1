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
	char		**line;
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

static t_object		add_new_cone(int fd, char **line)
{
	t_object	cone;

	cone.typpe = CONE;
	cone.angle = M_PI / 6;
	cone.direction = normalize_vector(vector(0, 1, 0));
	cone.center = point(0, 0, 0);
	cone.color = color(255, 255, 255, 0);
	cone.name = "Cone";
	cone = parse_object(fd, &cone);
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

static t_object		add_new_cylinder(int fd, char **line)
{
	t_object	cylinder;

	cylinder.typpe = CYLINDER;
	cylinder.radius = 1;
	cylinder.direction = normalize_vector(vector(0, 1, 0));
	cylinder.point = point(0, 0, 0);
	cylinder.color = color(255, 255, 255, 0);
	cylinder.name = "Cylinder";
	cylinder = parse_object(fd, &cylinder);
	return (cylinder);
}

t_object			add_new_object(int fd, char *type)
{
	char		**line;

	if (ft_strequ(type, "cylinder"))
		return (add_new_cylinder(fd, line));
	else if (ft_strequ(type, "sphere"))
		return (add_new_sphere(fd));
	else if (ft_strequ(type, "plane"))
		return (add_new_plane(fd));
	else
		return (add_new_cone(fd, line));
}
