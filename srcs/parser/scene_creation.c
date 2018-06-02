/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 16:48:17 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/06/02 17:52:58 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_scene		create_scene(t_env *env, char *file_name)
{
	int			fd;
	char		**line;
	t_scene		scene;

	if ((fd = open(file_name, O_RDONLY)) <= 2)
		exit_error(env);
	scene.object
	while ((line = split_new_line(fd)))
	{
		
	}
}
