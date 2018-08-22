/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:58:44 by aabelque          #+#    #+#             */
/*   Updated: 2018/08/22 12:35:26 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			opencl_draw(t_opencl *opcl, t_env *e)
{
	opcl->err = 0;

	opcl->err = clEnqueueWriteBuffer(opcl->commands, opcl->structobj, CL_TRUE,
			0, sizeof(t_object) * e->scene.objects_count,
			(void *)e->scene.objects, 0, NULL, NULL);
	if (opcl->err != CL_SUCCESS)
		printf("Error enqueuing objects %d\n", opcl->err);
	else
		ft_putendl("Objects enqueuing sucessful");

	opcl->err = clEnqueueWriteBuffer(opcl->commands, opcl->structlight, CL_TRUE,
			0, sizeof(t_light) * e->scene.lights_count, (void *)e->scene.lights, 0,
			NULL, NULL);
	if (opcl->err != CL_SUCCESS)
		printf("Error enqueuing lights %d\n", opcl->err);
	else
		ft_putendl("Lights enqueuing sucessful");

	opcl->err = clEnqueueWriteBuffer(opcl->commands, opcl->input_cam, CL_TRUE, 0,
			sizeof(t_camera), (void *)&e->camera, 0, NULL, NULL);
	if (opcl->err != CL_SUCCESS)
		printf("Error enqueuing camera %d\n", opcl->err);
	else
		ft_putendl("Camera enqueuing sucessful");

	opcl->err = clEnqueueWriteBuffer(opcl->commands, opcl->input_scene, CL_TRUE, 0,
			sizeof(t_scene), (void *)&e->scene, 0, NULL, NULL);
	if (opcl->err != CL_SUCCESS)
		printf("Error enqueuing scene %d\n", opcl->err);
	else
		ft_putendl("Scene enqueuing sucessful");

	opcl->err = clSetKernelArg(opcl->kernel, 0, sizeof(cl_mem),
			&opcl->output);
	if (opcl->err != CL_SUCCESS)
		printf("Error kernel Arg output%d\n", opcl->err);
	opcl->err |= clSetKernelArg(opcl->kernel, 1, sizeof(cl_mem),
			&opcl->input_scene);
	if (opcl->err != CL_SUCCESS)
		printf("Error kernel Arg scene %d\n", opcl->err);
	opcl->err |= clSetKernelArg(opcl->kernel, 2, sizeof(cl_mem),
			&opcl->input_cam);
	if (opcl->err != CL_SUCCESS)
		printf("Error kernel Arg cam %d\n", opcl->err);
	opcl->err |= clSetKernelArg(opcl->kernel, 3, sizeof(cl_mem),
			&opcl->structobj);
	if (opcl->err != CL_SUCCESS)
		printf("Error kernel Arg obj %d\n", opcl->err);
	opcl->err |= clSetKernelArg(opcl->kernel, 4, sizeof(cl_mem),
			&opcl->structlight);
	if (opcl->err != CL_SUCCESS)
		printf("Error enqueuing args array %d\n", opcl->err);
	else
		ft_putendl("Args enqueuing sucessful");
		
	opcl->err = clEnqueueNDRangeKernel(opcl->commands, opcl->kernel,
			2, NULL, opcl->imgxy, NULL, 0, NULL, NULL);
	if (opcl->err != CL_SUCCESS)
		printf("Error enqueuing xy array %d\n", opcl->err);
	else
		ft_putendl("XY enqueuing sucessful");
		
	// opcl->err = clEnqueueReadBuffer(opcl->commands, opcl->output, CL_TRUE, 0,
	// 		ft_strlen((char *)e->img_str), e->img_str, 0, NULL, NULL);
	// if (opcl->err != CL_SUCCESS)
	// 	printf("Error enqueuing output %d\n", opcl->err);
	// else
	// 	ft_putendl("Output enqueuing sucessful");

	size_t origin[3] = {WIN_WIDTH, WIN_HEIGHT, 1};
	size_t region[3] = {0, 0, 0};
	size_t row_pitch = WIN_WIDTH * sizeof(int);
	size_t slice_pitch = 0;
	
	opcl->err = clEnqueueReadImage(opcl->commands, opcl->output, CL_TRUE, region,
			origin, 0, 0, e->img_str, 0, NULL, NULL);
	if (opcl->err != CL_SUCCESS)
		printf("Error enqueuing output %d\n", opcl->err);
	else
		ft_putendl("Output enqueuing sucessful");

	//ft_ocl_init_error(opcl->err);

	cl_ulong maxMemAlloc;
	clGetDeviceInfo(opcl->device_id, CL_DEVICE_MAX_MEM_ALLOC_SIZE,
			sizeof(cl_ulong), &maxMemAlloc, NULL);
	//printf("Max mem size is: %llu\n", maxMemAlloc);
}
