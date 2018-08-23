/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 15:12:45 by aabelque          #+#    #+#             */
/*   Updated: 2018/08/22 15:32:58 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_cone(t_object *cone)
{
	cone->typpe = CONE;
	cone->angle = M_PI / 6;
	cone->direction = normalize_vector(vector(0, 1, 0));
	cone->center = point(0, 0, 0);
	cone->color = color(255, 255, 255, 0);
	cone->name = "Cone";
}

void		init_cylinder(t_object *cylinder)
{
	cylinder->typpe = CYLINDER;
	cylinder->radius = 1;
	cylinder->direction = normalize_vector(vector(0, 1, 0));
	cylinder->point = point(0, 0, 0);
	cylinder->color = color(255, 255, 255, 0);
	cylinder->name = "Cylinder";
}
