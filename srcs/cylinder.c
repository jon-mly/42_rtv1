#include "rtv1.h"

/*
** Calculate the norm of the ray from the origin of it to the intersection
** with the cylinder given in parameter.
** Returns the ray with "intersect" and "norm" values set up
*/

t_ray		cylinder_intersection(t_ray ray, t_cylinder cylinder)
{
	t_vector	distance;
	double		a;
	double		b;
	double		c;
	double		discriminant;

//	printf("Cylinder: x/y/z=%.2f/%.2f/%.2f - radius=%.2f - direction x/y/z=%.2f/%.2f/%.2f\n", cylinder.point.x, cylinder.point.y, cylinder.point.z, cylinder.radius, cylinder.direction.x, cylinder.direction.y, cylinder.direction.z);
	distance = vector_points(cylinder.point, ray.origin);
	a = dot_product(ray.direction, ray.direction) -
		pow(dot_product(ray.direction, cylinder.direction), 2);
	b = 2 * (dot_product(ray.direction, distance) - dot_product(ray.direction,
		cylinder.direction) * dot_product(distance, cylinder.direction));
	c = dot_product(distance, distance) - pow(dot_product(distance,
		cylinder.direction), 2) - pow(cylinder.radius, 2);
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
	}
	return (ray);
}
