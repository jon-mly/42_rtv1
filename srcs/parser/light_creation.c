/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 15:36:32 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/06/02 17:53:04 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Add a new light to the list of lights that compose the scene to create.
** Takes the file descriptor of the file that is being read, and the pointer
** on the lights already created (NULL if empty).
** Realloc the pointer with the current lights + 1.
** If sone parameters are not precised, default values will be set.
*/

static void			extend_lights(t_light **lights, int count)
{
	int			i;
	t_light		*new_lights;

	if (*lights == NULL)
	{
		if ((*light = (t_light*)malloc(sizeof(t_light))))
			return (NULL);
	}
	else
	{
		if ((new_lights = (t_light*)malloc(sizeof(t_light) * (count + 1))))
			return (NULL);
		i = -1;
		while (++i < count)
			new_lights[i] = (*lights)[i];
		ft_memdel(lights);
		*lights = new_lights;
	}
}

t_light				*add_light(int fd, t_light *existing_lights, int count)
{
	char		**line;
	t_light		new_light;

	extend_lights(&existing_lights, count);
	new_light->type = OMNI;
	new_light->position = point(0, 0, 0);
	new_light->color = color(255, 255, 255, 0);
	while ((line = split_new_line(fd)) && ft_strequ(line[0], "}") == FALSE)
	{
		if (line_len(line) == 4 && ft_strequ(line[0], "position")) //TODO: check nb of coord.
			new_light->position = point(ft_atoi(line[1], ft_atoi(line[2],
							ft_atoi[3])));
		else if (line_len(line) == 4 && ft_strequ(line[0], "color"))
			new_light->color = color(ft_atoi(line[1]), ft_atoi(line[2],
						ft_atoi(line[3]), 0));
		clear_line(line);
	}
	existing_lights[count] = new_light;
	return (existing_lights);
}
