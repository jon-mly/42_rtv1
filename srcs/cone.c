#include "rtv1.h"

/*
** Calculate the norm of the ray from the origin of it to the intersection
** with the cylinder given in parameter.
** Returns the ray with "intersect" and "norm" values set up
*/

t_ray		cone_intersection(t_ray ray, t_cone cone)
{
	t_vector	distance;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	distance = vector_points(cone.center, ray.origin);
	a = dot_product(ray.direction, ray.direction) - (1 + pow(tan(cone.angle),
		2)) * pow(dot_product(ray.direction, cone.direction), 2);
	b = 2 * (dot_product(ray.direction, distance) - (1 + pow(tan(cone.angle),
		2)) * dot_product(ray.direction, cone.direction) *
		dot_product(distance, cone.direction));
	c = dot_product(distance, distance) - (1 + pow(tan(cone.angle), 2)) *
		pow(dot_product(distance, cone.direction), 2);
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
