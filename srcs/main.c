/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:44 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/08/11 11:05:50 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		main(int ac, char **av)
{
	t_env		*env;
	int			device;

	device = 0;
	if (ac != 3)
		exit_usage();
	if (ft_strequ(av[1], "-cpu"))
		device = 1;
	env = init_env(av[2]);
	if (device == 1)
		calculate_scene(env);
	else
	{
		set_opencl_env(&env->opcl);
		opencl_init(&env->opcl, env);
		opencl_draw(&env->opcl, env);
	}
	if ((mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0)) == -1)
		ft_putendl("Failed to put image to window");
	mlx_hook(env->win_ptr, 2, 0, handle_key_event, (void*)env);
	mlx_hook(env->win_ptr, 17, 0, exit_properly, (void*)env);
	mlx_hook(env->win_ptr, 4, (1L<<2), debug_mouse_event, (void*)env);
	mlx_loop_hook(env->mlx_ptr, expose_event, (void*)env);
	mlx_loop(env->mlx_ptr);
	return (0);
}
