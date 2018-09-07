/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:27 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/09/07 11:31:14 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		setup_window(t_env *env)
{
	int		bpp;
	int		s_l;
	int		endian;

	env->mlx_ptr = mlx_init();
	env->win_ptr = mlx_new_window(env->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
		"RT v1");
	env->win_height = WIN_HEIGHT;
	env->win_width = WIN_WIDTH;
	if (env->mlx_ptr == NULL || env->win_ptr == NULL)
		exit_error(env);
	env->img_ptr = mlx_new_image(env->mlx_ptr, env->win_width, env->win_height);
	env->img_width = WIN_WIDTH;
	env->img_height = WIN_HEIGHT;
	env->img_str = mlx_get_data_addr(env->img_ptr, &bpp, &s_l,
		&endian);
	if (env->img_ptr == NULL || env->img_str == NULL)
		exit_error(env);
	env->line_size = s_l / 4;
	env->bpp = bpp;
	env->endian = endian;
}

t_env			*init_env(char *file_name)
{
	t_env	*env;
	int		fd;

	if ((fd = open(file_name, O_RDONLY)) <= 2)
		exit_usage();
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	env->mlx_ptr = NULL;
	env->img_ptr = NULL;
	env->img_str = NULL;
	env->win_ptr = NULL;
	setup_window(env);
	env->camera = init_camera(env);
	env->scene = create_scene(env, file_name, fd);
	return (env);
}
