#include "rtv1.h"

static t_object		get_sample_cone(void)
{
	t_object	object;
	t_cone		*cone;

	object.type = CONE;
	cone = (t_cone*)malloc(sizeof(t_cone));
	object.object = (void*)cone;
	cone->angle = M_PI / 12;
	cone->direction = normalize_vector(vector(0, -1, 0));
	cone->center = point(0, 0, 100);
	object.color = color(100, 100, 255, 0);
	return (object);
}

static t_object		get_sample_cylinder(void)
{
	t_object	object;
	t_cylinder	*cylinder;

	object.type = CYLINDER;
	cylinder = (t_cylinder*)malloc(sizeof(t_cylinder));
	object.object = (void*)cylinder;
	cylinder->radius = 0.8;
	cylinder->direction = normalize_vector(vector(1, 1, 1));
	cylinder->point = point(0, 0, 10);
	object.color = color(100, 100, 255, 0);
	return (object);
}

static t_object		get_sample_sphere(void)
{
	t_object	object;
	t_sphere	*sphere;

	object.type = SPHERE;
	sphere = (t_sphere*)malloc(sizeof(t_sphere));
	object.object = (void*)(sphere);
	sphere->radius = 0.8;
	sphere->center = point(2.0, 0.0, 8.0);
	object.color = color(100, 200, 200, 0);
	return (object);
}

static t_object		get_sample_plane(void)
{
	t_object	object;
	t_plane		*plane;

	object.type = PLANE;
	plane = (t_plane*)malloc(sizeof(t_plane));
	object.object = (void*)(plane);
	plane->normal = vector(0, 1, 0);
	plane->point = point(0, 0, 0);
	object.color = color(20, 200, 100, 0);
	return (object);
}

static t_light		get_sample_lighting(void)
{
	t_light		light;

	light.type = OMNI;
	light.position = point(-3, 0, -3);
	light.color = color(255, 255, 255, 0);
	return (light);
}

t_scene		get_sample_scene(void)
{
	t_scene		scene;

	scene.objects_count = 1;
	scene.objects = (t_object*)malloc(sizeof(t_object));
	scene.objects[0] = get_sample_sphere();
	scene.lights_count = 1;
	scene.lights = (t_light*)malloc(sizeof(t_light));
	scene.lights[0] = get_sample_lighting();
	return (scene);
}
