/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:27 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/05/22 11:46:28 by jmlynarc         ###   ########.fr       */
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
	env->img_str = (unsigned char*)(mlx_get_data_addr(env->img_ptr, &bpp, &s_l,
		&endian));
	if (env->img_ptr == NULL || env->img_str == NULL)
		exit_error(env);
	env->line_size = s_l / 4;
	env->bpp = bpp;
	env->endian = endian;
}

t_env			*init_env(void)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	env->mlx_ptr = NULL;
	env->img_ptr = NULL;
	env->img_str = NULL;
	env->win_ptr = NULL;
	setup_window(env);
	env->camera = init_camera(env);
	ft_putendl("Camera successfully set up");
	env->scene = get_sample_scene();
	ft_putendl("Scene successfully set up");
	return (env);
}
