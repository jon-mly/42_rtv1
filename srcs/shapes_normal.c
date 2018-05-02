#include "rtv1.h"

static t_vector		cone_normal(t_ray ray, t_cone cone)
{
	t_vector	normal;

	return (normal);
}

static t_vector		cylinder_normal(t_ray ray, t_cylinder cylinder)
{
	t_vector	normal;

	return (normal);
}

static t_vector		sphere_normal(t_ray ray, t_sphere sphere)
{
	t_vector	normal;

	normal = vector_points(sphere.center, ray.intersection);
	return (normalize_vector(normal));
}

static t_vector		plane_intersection(t_ray ray, t_plane plane)
{
	t_vector	normal;

	if (cos(dot_product(ray.direction, plane.normal)) <= 0)
		return (plane.normal);
	normal.x = -(plane.normal.x);
	normal.y = -(plane.normal.y);
	normal.z = -(plane.normal.z);
	return (normal);
}

t_vector			shape_normal(t_ray ray, t_object object)
{
	t_point		intersection;

	if (object.type == SPHERE)
		return (sphere_normal(ray, *((t_sphere*)(object.object))));
	else if (object.type == PLANE)
		return (plane_normal(ray, *((t_plane*)(object.object))));
	else if (object.type == CYLINDER)
		return (cylinder_normal(ray, *((t_cylinder*)(object.object))));
	else
		return (cone_normal(ray, *((t_cone*)(object.object)));
}
