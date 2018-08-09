/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:58:44 by aabelque          #+#    #+#             */
/*   Updated: 2018/07/25 11:59:20 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			opencl_draw(t_opencl *opcl, t_env *e)
{
	size_t		i;

	i = 0;
	opcl->err = 0;
	opcl->err = clEnqueueWriteBuffer(opcl->commands, opcl->input, CL_TRUE, 0,
			sizeof(t_fractal), (void *)&e->fra, 0, NULL, NULL);
	while (i < 5)
	{
		opcl->err |= clSetKernelArg(opcl->kernel[i], 0, sizeof(cl_mem),
				&opcl->output);
		opcl->err |= clSetKernelArg(opcl->kernel[i], 1, sizeof(cl_mem),
				&opcl->input);
		i++;
	}
	opcl->err = clEnqueueNDRangeKernel(opcl->commands, opcl->kernel[e->fractol],
			2, NULL, opcl->imgxy, NULL, 0, NULL, NULL);
	opcl->err = clEnqueueReadBuffer(opcl->commands, opcl->output, CL_TRUE, 0,
			sizeof(int) * opcl->img_s, e->img.addr, 0, NULL, NULL);
}
