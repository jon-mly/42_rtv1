#include "rtv1.h"

static t_object		get_sample_sphere(void)
{
	t_object	object;
	t_sphere	*sphere;

	object.type = SPHERE;
	sphere = (t_sphere*)malloc(sizeof(t_sphere));
	sphere->radius = 0.5;
	sphere->center = point(2.0, 0.0, 15.0);
	sphere->color = color(100, 200, 200, 0);
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
