#include "rtv1.h"

t_object			intersect_object(t_object ray, t_object object)
{
	if (object.type == SPHERE)
		ray = sphere_intersection(ray, object);
	else if (object.type == PLANE)
		ray = plane_intersection(ray, object);
	else if (object.type == CYLINDER)
		ray = cylinder_intersection(ray, object);
	else if (object.type == CONE)
		ray = cone_intersection(ray, object);
	if (ray.intersect)
	{
		ray.intersection.x = ray.origin.x + ray.direction.x * ray.norm;
		ray.intersection.y = ray.origin.y + ray.direction.y * ray.norm;
		ray.intersection.z = ray.origin.z + ray.direction.z * ray.norm;
	}
	return (ray);
}
