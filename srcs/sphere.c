#include "rtv1.h"

/*
** Calculate the norm of the ray from the origin of it to the intersection
** with the sphere given in parameter.
** Returns the ray with "intersect" and "norm" values set up
*/

t_ray		sphere_intersection(t_ray ray, t_sphere sphere)
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
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		ray.intersect = FALSE;
	else
	{
		ray.intersect = TRUE;
		ray.norm = (fmin((-b - sqrt(discriminant)) / (2 * a),
			(-b + sqrt(discriminant) / (2 * a))));
	}
	return (ray);
}
