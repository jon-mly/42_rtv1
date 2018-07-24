#include "rtv1.h"

/*
** Calculate the norm of the ray from the origin of it to the intersection
** with the sphere given in parameter.
** Returns the ray with "intersect" and "norm" values set up
*/

t_ray	sphere_intersection(t_ray ray, t_sphere sphere)
{
	double		a;
	double		b;
	double		c;
	double		discriminant;
	t_vector	distance;

	distance = vector_points(sphere.center, ray.origin);
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(ray.direction, distance);
	c = dot_product(distance, distance) - pow(sphere.radius, 2);
	ray.norm = closest_distance_quadratic(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
/*
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		ray.intersect = FALSE;
	else
	{
		ray.norm = (fmin((-b - sqrt(discriminant)) / (2 * a),
					(-b + sqrt(discriminant) / (2 * a))));
		ray.intersect = TRUE;
	}
	return (ray);*/
}

t_vector		sphere_normal(t_ray ray, t_sphere sphere)
{
	t_vector	normal;

	normal = vector_points(sphere.center, ray.intersection);
	return (normalize_vector(normal));
}
