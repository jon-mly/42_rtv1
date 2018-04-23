#include "rtv1.h"

static t_object		get_sample_sphere(void)
{
	t_object	object;
	t_sphere	*sphere;
	t_point		center;
	t_color		color;

	center.x = 2.0;
	center.z = 10.0;
	center.y = 0.0;
	color.r = 100;
	color.g = 200;
	color.b = 200;
	color.a = 255;
	object.type = SPHERE;
	sphere = (t_sphere*)malloc(sizeof(t_sphere));
	sphere->radius = 0.5;
	sphere->center = center;
	sphere->color = color;
	return (object);
}

t_scene		get_sample_scene(void)
{
	t_scene		scene;

	scene.objects_count = 1;
	scene.objects = (t_object*)malloc(sizeof(t_object));
	scene.objects[0] = get_sample_sphere();
	return (scene);
}
