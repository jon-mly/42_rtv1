/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 16:42:08 by aabelque          #+#    #+#             */
/*   Updated: 2018/08/09 14:12:16 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		opencl_free(t_opencl *opcl)
{
	clReleaseProgram(opcl->program);
	clReleaseKernel(opcl->kernel);
	clReleaseCommandQueue(opcl->commands);
	clReleaseContext(opcl->context);
}
