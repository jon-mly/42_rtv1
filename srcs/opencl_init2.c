/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:07:23 by aabelque          #+#    #+#             */
/*   Updated: 2018/08/09 14:51:54 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	opencl_init2(t_opencl *opcl, t_env *e)
{
	opcl->img_s = WIN_WIDTH * WIN_HEIGHT;
	//opcl->bufhst = (int *)ft_memalloc(opcl->img_s * sizeof(int));
	//opcl->structobj = clCreateBuffer(opcl->context, CL_MEM_READ_ONLY,
	//		sizeof(t_object) * e->scene.objects_count, NULL, NULL);
	opcl->input_scene = clCreateBuffer(opcl->context, CL_MEM_READ_ONLY,
			sizeof(t_scene), NULL, NULL);
	opcl->input_cam = clCreateBuffer(opcl->context, CL_MEM_READ_ONLY,
			sizeof(t_camera), NULL, NULL);
	opcl->output = clCreateBuffer(opcl->context, CL_MEM_WRITE_ONLY,
			sizeof(int) * opcl->img_s, NULL, NULL);
	create_prog(opcl);
	create_kernel(opcl->program, &opcl->kernel, "pixel_raytracing_gpu");
}
