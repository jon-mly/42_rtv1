/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:57 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/06/01 15:20:26 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_object		get_sample_cone(void)
{
	t_object	object;
	t_cone		*cone;

	object.type = CONE;
	object.name = "cone";
	cone = (t_cone*)malloc(sizeof(t_cone));
	object.object = (void*)cone;
	cone->angle = M_PI / 9;
	cone->direction = normalize_vector(vector(4, -2, 3));
	cone->center = point(-9, 10, 70);
	object.color = color(100, 100, 255, 0);
	cone->color = object.color;
	return (object);
}

static t_object		get_sample_cylinder(void)
{
	t_object	object;
	t_cylinder	*cylinder;

	object.type = CYLINDER;
	object.name = "cylinder";
	cylinder = (t_cylinder*)malloc(sizeof(t_cylinder));
	object.object = (void*)cylinder;
	cylinder->radius = 2;
	cylinder->direction = normalize_vector(vector(1, 1, 1));
	cylinder->point = point(0, 10, 70);
	object.color = color(255, 10, 10, 0);
	cylinder->color = object.color;
	return (object);
}

static t_object		get_sample_sphere(void)
{
	t_object	object;
	t_sphere	*sphere;

	object.type = SPHERE;
	object.name = "sphere";
	sphere = (t_sphere*)malloc(sizeof(t_sphere));
	sphere->radius = 5;
	sphere->center = point(10, 11.5, 6);
	object.object = (void*)(sphere);
	object.color = color(100, 200, 255, 0);
	sphere->color = object.color;
	return (object);
}

static t_object		get_sample_plane(void)
{
	t_object	object;
	t_plane		*plane;

	object.type = PLANE;
	object.name = "horizontal plane";
	plane = (t_plane*)malloc(sizeof(t_plane));
	plane->normal = normalize_vector(vector(0, 1, 0));
	plane->point = point(0, 0, 0);
	object.object = (void*)(plane);
	object.color = color(20, 200, 100, 0);
	plane->color = object.color;
	return (object);
}

static t_object		get_sample_plane_2(void)
{
	t_object	object;
	t_plane		*plane;

	object.type = PLANE;
	object.name = "vertical plane";
	plane = (t_plane*)malloc(sizeof(t_plane));
	plane->normal = normalize_vector(vector(0, 0, -1));
	plane->point = point(13, 0, 30);
	object.object = (void*)(plane);
	object.color = color(200, 20, 100, 0);
	plane->color = object.color;
	return (object);
}
static t_light		get_sample_lighting(void)
{
	t_light		light;

	light.type = OMNI;
	light.position = point(-10, 3, -20);
	light.color = color(255, 255, 255, 0);
	return (light);
}

t_scene		get_sample_scene(void)
{
	t_scene		scene;

	scene.objects_count = 1;
	scene.objects = (t_object*)malloc(sizeof(t_object) * scene.objects_count);
//	scene.objects[3] = get_sample_plane();
//	scene.objects[4] = get_sample_plane_2();
//	scene.objects[2] = get_sample_sphere();
	scene.objects[0] = get_sample_cylinder();
//	scene.objects[1] = get_sample_cone();
	scene.lights_count = 1;
	scene.lights = (t_light*)malloc(sizeof(t_light) * scene.lights_count);
	scene.lights[0] = get_sample_lighting();
	return (scene);
}
