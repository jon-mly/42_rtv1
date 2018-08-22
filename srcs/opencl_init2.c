/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:07:23 by aabelque          #+#    #+#             */
/*   Updated: 2018/08/22 12:17:43 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	opencl_init2(t_opencl *opcl, t_env *e)
{
	void * mainmem = NULL;
	size_t mainsizebuf;
	t_object	*object = (t_object *)e->scene.objects;

	opcl->img_s = WIN_WIDTH * WIN_HEIGHT;
	
	//printf("Camera : position %.2f, %.2f, %.2f\n", e->camera.spot.x, e->camera.spot.y, e->camera.spot.z);
	opcl->format = (cl_image_format){.image_channel_order = CL_RGBA,
		.image_channel_data_type = CL_UNSIGNED_INT8};
	opcl->desc = (cl_image_desc){.image_type = CL_MEM_OBJECT_IMAGE2D,
		.image_width = WIN_WIDTH, .image_height = WIN_HEIGHT,
		.image_depth = 1, .image_array_size = 0,
		.image_row_pitch = 0, .image_slice_pitch = 0,
		.num_mip_levels = 0, .num_samples = 0, .buffer = NULL};

	opcl->output = clCreateImage(opcl->context,
			CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR, &opcl->format,
			&opcl->desc, NULL, &opcl->err);
	if (opcl->err != CL_SUCCESS)
		printf("Error create buffer image %d\n", opcl->err);

	opcl->structobj = clCreateBuffer(opcl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_object) * e->scene.objects_count, e->scene.objects, NULL);
	if (opcl->err != CL_SUCCESS)
		printf("Error create buffer obj %d\n", opcl->err);

	printf("Type : %u\n", object->typpe);
	mainmem = NULL;
	mainsizebuf = 0;
	clGetMemObjectInfo(opcl->structobj, CL_MEM_SIZE, sizeof(mainsizebuf),
			&mainsizebuf, NULL);
	clGetMemObjectInfo(opcl->structobj, CL_MEM_HOST_PTR, sizeof(mainmem),
			&mainmem, NULL);
	//printf("Object buffer size: %lu\n", mainsizebuf);
	//printf("Object buffer memory address: %p\n", mainmem);

	opcl->structlight = clCreateBuffer(opcl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_light) * e->scene.lights_count, e->scene.lights, NULL);
	if (opcl->err != CL_SUCCESS)
		printf("Error create buffer light %d\n", opcl->err);

	mainmem = NULL;
	mainsizebuf = 0;
	clGetMemObjectInfo(opcl->structlight, CL_MEM_SIZE, sizeof(mainsizebuf),
			&mainsizebuf, NULL);
	clGetMemObjectInfo(opcl->structlight, CL_MEM_HOST_PTR, sizeof(mainmem),
			&mainmem, NULL);
	//printf("Light buffer size: %lu\n", mainsizebuf);
	//printf("Light buffer memory address: %p\n", mainmem);

	opcl->input_scene = clCreateBuffer(opcl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_scene), &e->scene, NULL);
	if (opcl->err != CL_SUCCESS)
		printf("Error create buffer scene %d\n", opcl->err);

	mainmem = NULL;
	mainsizebuf = 0;
	clGetMemObjectInfo(opcl->input_scene, CL_MEM_SIZE, sizeof(mainsizebuf),
			&mainsizebuf, NULL);
	clGetMemObjectInfo(opcl->input_scene, CL_MEM_HOST_PTR, sizeof(mainmem),
			&mainmem, NULL);
	//printf("Scene buffer size: %lu\n", mainsizebuf);
	//printf("Scene buffer memory address: %p\n", mainmem);

	opcl->input_cam = clCreateBuffer(opcl->context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_camera), &e->camera, NULL);
	if (opcl->err != CL_SUCCESS)
		printf("Error create buffer cam %d\n", opcl->err);

	mainmem = NULL;
	mainsizebuf = 0;
	clGetMemObjectInfo(opcl->input_cam, CL_MEM_SIZE, sizeof(mainsizebuf),
			&mainsizebuf, NULL);
	clGetMemObjectInfo(opcl->input_cam, CL_MEM_HOST_PTR, sizeof(mainmem),
			&mainmem, NULL);
	//printf("Camera buffer size: %zu\n", mainsizebuf);
	//printf("Camera buffer memory address: %p\n", mainmem);

//	opcl->output = clCreateBuffer(opcl->context, CL_MEM_WRITE_ONLY,
//			sizeof(int) * opcl->img_s, NULL, &opcl->err);
//	if (opcl->err != CL_SUCCESS)
//		printf("Error create buffer output %d\n", opcl->err);
	create_prog(opcl);
	create_kernel(opcl->program, &opcl->kernel, "pixel_raytracing_gpu");
	//opcl->output = clCreateBuffer(opcl->context, CL_MEM_WRITE_ONLY,
	//		sizeof(int) * opcl->img_s, NULL, NULL);
}
