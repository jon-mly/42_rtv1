/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:44 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/09/07 12:00:28 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				main(int ac, char **av)
{
	t_env		*env;

	if (ac != 2)
		exit_usage();
	env = init_env(av[1]);
	calculate_scene(env);
	if ((mlx_put_image_to_window(env->mlx_ptr, env->win_ptr,
					env->img_ptr, 0, 0)) == -1)
		ft_putendl("Failed to put image to window");
	mlx_hook(env->win_ptr, 2, 0, handle_key_event, (void*)env);
	mlx_hook(env->win_ptr, 17, 0, exit_properly, (void*)env);
	mlx_loop_hook(env->mlx_ptr, expose_event, (void*)env);
	mlx_loop(env->mlx_ptr);
	return (0);
}
