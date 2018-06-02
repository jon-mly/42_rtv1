/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:44 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/06/02 15:26:13 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		main(int ac, char **av)
{
	t_env		*env;

	(void)ac;
	(void)av;
	env = init_env();
	calculate_scene(env);
	mlx_loop_hook(env->mlx_ptr, expose_event, (void*)env);
	mlx_key_hook(env->win_ptr, handle_key_event, (void*)env);
	mlx_loop(env->mlx_ptr);
	return (0);
}
