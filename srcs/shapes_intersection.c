#include "rtv1.h"

/*
 ** Calculate the norm of the ray from the origin of it to the intersection
 ** with the cylinder given in parameter.
 ** Returns the ray with "intersect" and "norm" values set up
 */

/*
static t_ray	cone_intersection(t_ray ray, t_cone cone)
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
}*/

/*
 ** Calculate the norm of the ray from the origin of it to the intersection
 ** with the cylinder given in parameter.
 ** Returns the ray with "intersect" and "norm" values set up
 */
/*
static t_ray	cylinder_intersection(t_ray ray, t_cylinder cylinder)
{
	t_vector	distance;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	distance = vector_points(cylinder.point, ray.origin);
	a = dot_product(ray.direction, ray.direction) -
		pow(dot_product(ray.direction, cylinder.direction), 2);
	b = 2 * (dot_product(ray.direction, distance) - (dot_product(ray.direction,
				cylinder.direction) * dot_product(distance, cylinder.direction)));
	c = dot_product(distance, distance) - pow(dot_product(distance,
				cylinder.direction), 2) - pow(cylinder.radius, 2);
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
}*/

/*
 ** Calculate the norm of the ray from the origin of it to the intersection
 ** with the plane given in parameter.
 ** Returns the ray with "intersect" and "norm" values set up
 */

static t_ray	plane_intersection(t_ray ray, t_plane plane)
{
	double			norm;

	if (dot_product(plane.normal, ray.direction) == 0)
	{
		ray.intersect = FALSE;
		return (ray);
	}
	norm = (dot_product(plane.normal, plane.point) - dot_product(plane.normal,
			ray.origin)) / dot_product(plane.normal, ray.direction);
	if (norm < 0.0001 || norm > 100000)
		ray.intersect = FALSE;
	else
	{
		ray.intersect = TRUE;
		ray.norm = norm;
	}
	return (ray);
}

/*
 ** Calculate the norm of the ray from the origin of it to the intersection
 ** with the sphere given in parameter.
 ** Returns the ray with "intersect" and "norm" values set up
 */

static t_ray	sphere_intersection(t_ray ray, t_sphere sphere)
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
		ray.norm = (fmin((-b - sqrt(discriminant)) / (2 * a),
					(-b + sqrt(discriminant) / (2 * a))));
		ray.intersect = TRUE;
	}
	return (ray);
}

t_ray			intersect_object(t_ray ray, t_object object)
{
	if (object.type == SPHERE)
		ray = sphere_intersection(ray, *((t_sphere*)(object.object)));
	else if (object.type == PLANE)
		ray = plane_intersection(ray, *((t_plane*)(object.object)));
	else if (object.type == CYLINDER)
		ray = cylinder_intersection(ray, *((t_cylinder*)(object.object)));
	else if (object.type == CONE)
		ray = cone_intersection(ray, *((t_cone*)(object.object)));
	if (ray.intersect)
	{
		ray.intersection.x = ray.origin.x + ray.direction.x * ray.norm;
		ray.intersection.y = ray.origin.y + ray.direction.y * ray.norm;
		ray.intersection.z = ray.origin.z + ray.direction.z * ray.norm;
	}
	return (ray);
}
