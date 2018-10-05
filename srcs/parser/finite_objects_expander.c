#include "rtv1.h"

static      t_scene create_cylinders_ends(t_object cylinder, t_scene scene)
{
    t_object      top_disc;
    t_object      bottom_disc;

    bottom_disc = (t_object){.typpe = DISC, .point = cylinder.point, .normal = cylinder.direction,
        .color = cylinder.color, .diffuse = cylinder.diffuse, .brillance = cylinder.brillance,
        .radius = cylinder.radius, .reflection = cylinder.reflection, .refraction = cylinder.refraction};
    top_disc = bottom_disc;
    top_disc.point = point_from_vector(bottom_disc.point, cylinder.direction, cylinder.height);
    scene.objects_count++;
    scene.objects = expand_objects(scene.objects, scene.objects_count);
	scene.objects[scene.objects_count - 1] = top_disc;
    scene.objects_count++;
    scene.objects = expand_objects(scene.objects, scene.objects_count);
	scene.objects[scene.objects_count - 1] = bottom_disc;
    return (scene);
}

static      t_scene create_cone_end(t_object cone, t_scene scene)
{
    t_object    top_disc;

    top_disc = (t_object){.typpe = DISC, .normal = cone.direction,
        .color = cone.color, .diffuse = cone.diffuse, .brillance = cone.brillance,
        .reflection = cone.reflection, .transparency = cone.transparency,
        .refraction = cone.refraction};
    top_disc.point = point_from_vector(cone.center, cone.direction, cone.height);
    top_disc.radius = cone.height * tan(cone.angle);
    scene.objects_count++;
    scene.objects = expand_objects(scene.objects, scene.objects_count);
	scene.objects[scene.objects_count - 1] = top_disc;
    return (scene);
}

/*
** For finite objects, will create the other objects that are required to
** compose the finite object.
** Assumes that the object given in parameter is finite.
*/

t_scene       create_dependant_objects(t_object object, int fd, t_scene scene)
{
    if (object.typpe == CYLINDER)
        scene = create_cylinders_ends(object, scene);
    else if (object.typpe == CONE)
        scene = create_cone_end(object, scene);
    return (scene);
}