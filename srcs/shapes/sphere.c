#include "rtv1.h"

/*
** Calculate the norm of the ray from the origin of it to the intersection
** with the sphere given in parameter.
** Returns the ray with "intersect" and "norm" values set up
*/

t_object	sphere_intersection(t_object ray, t_object sphere)
{
	float		a;
	float		b;
	float		c;
	t_vector	distance;

	distance = vector_points(sphere.center, ray.origin);
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(ray.direction, distance);
	c = dot_product(distance, distance) - pow(sphere.radius, 2);
	ray.norm = closest_distance_quadratic(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}

t_vector		sphere_normal(t_object ray, t_object sphere)
{
	t_vector	normal;

	normal = vector_points(sphere.center, ray.intersectiion);
	return (normalize_vector(normal));
}
