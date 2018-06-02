/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 16:09:07 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/06/02 17:53:01 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_object		add_new_sphere(int fd)
{
	char		**line;
	t_object	object;
	t_sphere	*sphere;

	object.type = SPHERE;
	sphere = (t_sphere*)malloc(sizeof(t_sphere));
	sphere->radius = 1;
	sphere->center = point(10, 12, 6);
	sphere->color = color(255, 255, 255, 0);
	while ((line = split_new_line(fd)) && ft_strequ(line[0], "}") == FALSE)
	{
		if (ft_strequ(line[0], "radius"))
			sphere->radius = ft_atoi(line[1]);
		else if (ft_strequ(line[0], "position"))
			sphere->position = point(ft_atoi(line[1]), ft_atoi(line[2]),
					ft_atoi(line[3]));
		else if (ft_strequ(line[0], "color"))
			sphere->color = color(ft_atoi(line[1]), ft_atoi(line[2]),
					ft_atoi(line[3]), 0);
	}
	object.object = (void*)sphere;
	return (object);
}

static t_object		add_new_plane(int fd)
{
	char		**line;
	t_object	object;
	t_sphere	*sphere;

	object.type = PLANE;
	plane = (t_plane*)malloc(sizeof(t_plane));
	plane->normal = normalize_vector(vector(0, 1, 0));
	plane->point = point(0, 0, 0);
	plane->color = color(255, 255, 255, 0);
	while ((line = split_new_line(fd)) && ft_strequ(line[0], "}") == FALSE)
	{
		if (ft_strequ(line[0], "normal"))
			plane->normal = normalize_vector(vector(ft_atoi(line[1]),
						ft_atoi(line[2]), ft_atoi(line[3])));
		else if (ft_strequ(line[0], "point"))
			plane->point = point(ft_atoi(line[1]), ft_atoi(line[2]),
					ft_atoi(line[3]));
		else if (ft_strequ(line[0], "color"))
			plane->color = color(ft_atoi(line[1]), ft_atoi(line[2]),
					ft_atoi(line[3]), 0);
	}
	object.object = (void*)plane;
	return (object);
}

static t_object		add_new_cone(int fd)
{
	char		**line;
	t_object	object;
	t_cone		*cone;

	object.type = CONE;
	cone = (t_cone*)malloc(sizeof(t_cone));
	cone->angle = M_PI / 6;
	cone->direction = normalize_vector(vector(0, 1, 0));
	cone->center = point(0, 0, 0);
	cone->color = color(255, 255, 255, 0);
	while ((line = split_new_line(fd)) && ft_strequ(line[0], "}") == FALSE)
	{
		if (ft_strequ(line[0], "pi_divider"))
			cone->angle = M_PI / ft_atoi(line[1]);
		else if (ft_strequ(line[0], "direction"))
			cone->direction = normalize_vector(vector(ft_atoi(line[1]),
						ft_atoi(line[2]), ft_atoi(line[3])));
		else if (ft_strequ(line[0], "center"))
			cone->center = point(ft_atoi(line[1]), ft_atoi(line[2]),
					ft_atoi(line[3]));
		else if (ft_strequ(line[0]), "color")
			cone->color = color(ft_atoi(line[1]), ft_atoi(line[2]),
					ft_atoi(line[3]), 0);
	}
	object.object = cone;
	return (object);
}

static t_object		add_new_cylinder(int fd)
{
	char		**line;
	t_object	object;
	t_cylinder	*cylinder;

	object.type = CYLINDER;
	cylinder = (t_cylinder*)malloc(sizeof(t_cylinder));
	cylinder->radius = 1;
	cylinder->direction = normalize_vector(vector(0, 1, 0));
	cylinder->point = point(0, 0, 0);
	cylinder->color = color(255, 255, 255, 0);
	while ((line = split_new_line(fd)) && ft_strequ(line[0], "}") == FALSE)
	{
		if (ft_strequ(line[0], "radius"))
			cylinder->radius = ft_atoi(line[1]);
		else if (ft_strequ(line[0]), "position")
			cylinder->point = point(ft_atoi(line[1]), ft_atoi(line[2]),
					ft_atoi(line[3]));
		else if (ft_strequ(line[0], "direction"))
			cylinder->direction = normalize_vector(vector(ft_atoi(line[1]),
						ft_atoi(line[2]), ft_atoi(line[3])));
		else if (ft_strequ(line[0], "color"))
			cylinder->color = color(ft_atoi(line[1]), ft_atoi(line[2]),
					ft_atoi(line[3]), 0);
	}
	object.object = cylinder;
	return (object);
}


