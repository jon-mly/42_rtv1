#include "rtv1.h"

static t_vector		cone_normal(t_ray ray, t_cone cone)
{
	t_vector	normal;
	t_point		pt_dir;
	t_point		pt_normal;
	double		distance;

	distance = cos(cone.angle) * points_norm(ray.intersection, cone.center);
	distance *= (dot_product(ray.direction, cone.direction) >= 0) ?
		-1 : 1;
	pt_dir.x = cone.center.x + distance * cone.direction.x;
	pt_dir.y = cone.center.y + distance * cone.direction.y;
	pt_dir.z = cone.center.z + distance * cone.direction.z;
	distance = points_norm(pt_dir, ray.intersection) / tan(cone.angle);
	distance *= (dot_product(ray.direction, cone.direction) >= 0) ?
		-1 : 1;
	pt_normal.x = pt_dir.x + distance * ray.direction.x;
	pt_normal.y = pt_dir.y + distance * ray.direction.y;
	pt_normal.z = pt_dir.z + distance * ray.direction.z;
	normal = vector_points(pt_normal, ray.intersection);
	return (normalize_vector(normal));
}

static t_vector		cylinder_normal(t_ray ray, t_cylinder cylinder)
{
	t_vector	normal;
	t_point		pt_normal;
	double		dist_normal;

	dist_normal = sqrt(pow(points_norm(ray.intersection, cylinder.point), 2) -
			pow(cylinder.radius, 2));
	dist_normal *= (dot_product(ray.direction, cylinder.direction) >= 0) ?
		-1 : 1;
	pt_normal.x = cylinder.point.x + dist_normal * cylinder.direction.x;
	pt_normal.y = cylinder.point.y + dist_normal * cylinder.direction.y;
	pt_normal.z = cylinder.point.z + dist_normal * cylinder.direction.z;
	normal = vector_points(pt_normal, ray.intersection);
	return (normalize_vector(normal));
}

static t_vector		sphere_normal(t_ray ray, t_sphere sphere)
{
	t_vector	normal;

	normal = vector_points(sphere.center, ray.intersection);
	return (normalize_vector(normal));
}

static t_vector		plane_normal(t_ray ray, t_plane plane)
{
	t_vector	normal;

	if (cos(dot_product(ray.direction, plane.normal)) <= 0)
		return (normalize_vector(plane.normal));
	normal.x = -(plane.normal.x);
	normal.y = -(plane.normal.y);
	normal.z = -(plane.normal.z);
	return (normalize_vector(normal));
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
		return (cone_normal(ray, *((t_cone*)(object.object))));
}