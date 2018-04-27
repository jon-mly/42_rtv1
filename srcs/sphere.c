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

//	printf("Sphere : x/y/z = %.2f/%.2f/%.2f - radius = %.2f\n", sphere.center.x, sphere.center.y, sphere.center.z, sphere.radius);
	distance = vector_points(sphere.center, ray.origin);
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(ray.direction, distance);
	c = dot_product(distance, distance) - pow(sphere.radius, 2);
//	printf("a=%.2e, b=%.2e, c=%.2e - ", a,b,c);
	discriminant = b * b - 4 * a * c;
//	printf("Disc = %.2E - ", discriminant);
	if (discriminant < 0)
		ray.intersect = FALSE;
	else
	{
		ray.intersect = TRUE;
		ray.norm = (fmin((-b - sqrt(discriminant)) / (2 * a),
			(-b + sqrt(discriminant) / (2 * a))));
		//printf("Norm = %.2f - ", ray.norm);
	}
	return (ray);
}
