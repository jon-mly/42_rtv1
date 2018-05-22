/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:31 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/05/22 11:46:32 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			handle_key_event(int key, void *param)
{
	t_env		*env;

	env = (t_env*)param;
	if (key == KEY_ESC)
		exit_normally(env);
	return (0);
}
