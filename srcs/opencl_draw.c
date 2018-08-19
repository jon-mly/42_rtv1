/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:58:44 by aabelque          #+#    #+#             */
/*   Updated: 2018/08/19 12:47:55 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			opencl_draw(t_opencl *opcl, t_env *e)
{
	opcl->err = 0;
	printf("Size t_vector = %lu\n", sizeof(t_vector));
	printf("Size t_object = %lu\n", sizeof(t_object));

	opcl->err = clEnqueueWriteBuffer(opcl->commands, opcl->structobj, CL_TRUE,
			0, sizeof(t_object) * e->scene.objects_count,
			(void *)e->scene.objects, 0, NULL, NULL);
	opcl->err = clEnqueueWriteBuffer(opcl->commands, opcl->structlight, CL_TRUE,
			0, sizeof(t_light) * e->scene.lights_count, (void *)e->scene.lights, 0,
			NULL, NULL);
	opcl->err = clEnqueueWriteBuffer(opcl->commands, opcl->input_cam, CL_TRUE, 0,
			sizeof(t_camera), (void *)&e->camera, 0, NULL, NULL);
	opcl->err = clEnqueueWriteBuffer(opcl->commands, opcl->input_scene, CL_TRUE, 0,
			sizeof(t_scene), (void *)&e->scene, 0, NULL, NULL);

	opcl->err = clSetKernelArg(opcl->kernel, 0, sizeof(cl_mem),
			&opcl->output);
	if (opcl->err != CL_SUCCESS)
		printf("error1\n");
	opcl->err = clSetKernelArg(opcl->kernel, 1, sizeof(cl_mem),
			&opcl->input_scene);
	if (opcl->err != CL_SUCCESS)
		printf("error2\n");
	opcl->err = clSetKernelArg(opcl->kernel, 2, sizeof(cl_mem),
			&opcl->input_cam);
	if (opcl->err != CL_SUCCESS)
		printf("error3\n");
	opcl->err = clSetKernelArg(opcl->kernel, 3, sizeof(cl_mem),
			&opcl->structobj);
	if (opcl->err != CL_SUCCESS)
		printf("error4\n");
	opcl->err = clSetKernelArg(opcl->kernel, 4, sizeof(cl_mem),
			&opcl->structlight);
	if (opcl->err != CL_SUCCESS)
		printf("error5\n");
	opcl->err = clEnqueueNDRangeKernel(opcl->commands, opcl->kernel,
			2, NULL, opcl->imgxy, NULL, 0, NULL, NULL);
	if (opcl->err != CL_SUCCESS)
		printf("error6\n");
	//clFinish(opcl->commands);
	//opcl->err = clEnqueueReadImage(opcl->commands, opcl->output, CL_TRUE, 0,
	//		opcl->imgxy, 0, 0, e->img_str, 0, NULL, NULL);
	opcl->err = clEnqueueReadBuffer(opcl->commands, opcl->output, CL_TRUE, 0,
			sizeof(int) * opcl->img_s, e->img_str, 0, NULL, NULL);
	if (opcl->err != CL_SUCCESS)
		printf("%d\n", opcl->err);
	//clFinish(opcl->commands);
}
