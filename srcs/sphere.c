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

	a = pow(ray.direction.x, 2) + pow(ray.direction.y, 2) +
		pow(ray.direction.y, 2);
	b = 2 * (ray.direction.x * (ray.origin.x - sphere.center.x) +
			ray.direction.y * (ray.origin.y - sphere.center.y) +
			ray.direction.z * (ray.origin.z - sphere.center.z));
	c = pow(ray.origin.x - sphere.center.x, 2) + pow(ray.origin.y -
		sphere.center.y, 2) + pow(ray.origin.z - sphere.center.z, 2) -
		pow(sphere.radius, 2);
	discriminant = quadratic_discriminant(a, b, c);
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
