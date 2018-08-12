/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:07:23 by aabelque          #+#    #+#             */
/*   Updated: 2018/08/12 15:25:04 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	opencl_init2(t_opencl *opcl, t_env *e)
{
	void * mainmem = NULL;
	size_t mainsizebuf;
	t_object	*object = (t_object *)e->scene.objects;

	opcl->img_s = WIN_WIDTH * WIN_HEIGHT;
	//opcl->bufhst = (int *)ft_memalloc(opcl->img_s * sizeof(int));

	opcl->structobj = clCreateBuffer(opcl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_object) * e->scene.objects_count, e->scene.objects, NULL);
	printf("Type : %u\n", object->typpe);
	mainmem = NULL;
	mainsizebuf = 0;
	clGetMemObjectInfo(opcl->structobj, CL_MEM_SIZE, sizeof(mainsizebuf),
			&mainsizebuf, NULL);
	clGetMemObjectInfo(opcl->structobj, CL_MEM_HOST_PTR, sizeof(mainmem),
			&mainmem, NULL);
	printf("Object buffer size: %lu\n", mainsizebuf);
	printf("Object buffer memory address: %p\n", mainmem);

	opcl->structlight = clCreateBuffer(opcl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_light) * e->scene.lights_count, e->scene.lights, NULL);
	mainmem = NULL;
	mainsizebuf = 0;
	clGetMemObjectInfo(opcl->structlight, CL_MEM_SIZE, sizeof(mainsizebuf),
			&mainsizebuf, NULL);
	clGetMemObjectInfo(opcl->structlight, CL_MEM_HOST_PTR, sizeof(mainmem),
			&mainmem, NULL);
	printf("Light buffer size: %lu\n", mainsizebuf);
	printf("Light buffer memory address: %p\n", mainmem);

	opcl->input_scene = clCreateBuffer(opcl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_scene), &(e->scene), NULL);

	mainmem = NULL;
	mainsizebuf = 0;
	clGetMemObjectInfo(opcl->input_scene, CL_MEM_SIZE, sizeof(mainsizebuf),
			&mainsizebuf, NULL);
	clGetMemObjectInfo(opcl->input_scene, CL_MEM_HOST_PTR, sizeof(mainmem),
			&mainmem, NULL);
	printf("Scene buffer size: %lu\n", mainsizebuf);
	printf("Scene buffer memory address: %p\n", mainmem);

	mainmem = NULL;
	mainsizebuf = 0;
	opcl->input_cam = clCreateBuffer(opcl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_camera), &e->camera, NULL);

	clGetMemObjectInfo(opcl->input_cam, CL_MEM_SIZE, sizeof(mainsizebuf),
			&mainsizebuf, NULL);
	clGetMemObjectInfo(opcl->input_cam, CL_MEM_HOST_PTR, sizeof(mainmem),
			&mainmem, NULL);
	printf("Camera buffer size: %lu\n", mainsizebuf);
	printf("Camera buffer memory address: %p\n", mainmem);

	opcl->output = clCreateBuffer(opcl->context, CL_MEM_WRITE_ONLY,
			sizeof(int) * opcl->img_s, NULL, NULL);

	create_prog(opcl);
	create_kernel(opcl->program, &opcl->kernel, "pixel_raytracing_gpu");
}
