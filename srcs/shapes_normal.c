#include "rtv1.h"

/*
** See proofs on paper for explainations.
*/

t_vector			shape_normal(t_object ray, t_object object)
{
	if (object.type == SPHERE)
		return (sphere_normal(ray, object));
	else if (object.type == PLANE)
		return (plane_normal(ray, object));
	else if (object.type == CYLINDER)
		return (cylinder_normal(ray, object));
	else
		return (cone_normal(ray, object));
}
