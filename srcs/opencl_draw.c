/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:58:44 by aabelque          #+#    #+#             */
/*   Updated: 2018/08/11 16:07:53 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			opencl_draw(t_opencl *opcl, t_env *e)
{
	opcl->err = 0;
	opcl->err = clEnqueueWriteBuffer(opcl->commands, opcl->structobj, CL_TRUE,
			0, sizeof(t_object) * e->scene.objects_count,
			(void *)&e->scene.objects, 0, NULL, NULL);
	opcl->err = clEnqueueWriteBuffer(opcl->commands, opcl->input_cam, CL_TRUE, 0,
			sizeof(t_camera), (void *)&e->camera, 0, NULL, NULL);
	opcl->err = clEnqueueWriteBuffer(opcl->commands, opcl->input_scene, CL_TRUE, 0,
			sizeof(t_scene), (void *)&e->scene, 0, NULL, NULL);
	opcl->err |= clSetKernelArg(opcl->kernel, 0, sizeof(cl_mem),
			&opcl->output);
	opcl->err |= clSetKernelArg(opcl->kernel, 1, sizeof(cl_mem),
			&opcl->input_scene);
	opcl->err |= clSetKernelArg(opcl->kernel, 2, sizeof(cl_mem),
			&opcl->input_cam);
	opcl->err |= clSetKernelArg(opcl->kernel, 3, sizeof(cl_mem),
			&opcl->structobj);
	opcl->err = clEnqueueNDRangeKernel(opcl->commands, opcl->kernel,
			2, NULL, opcl->imgxy, NULL, 0, NULL, NULL);
	opcl->err = clEnqueueReadBuffer(opcl->commands, opcl->output, CL_TRUE, 0,
			sizeof(int) * opcl->img_s, e->img_str, 0, NULL, NULL);
}
