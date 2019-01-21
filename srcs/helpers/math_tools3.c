#include "rtv1.h"

t_vector	scale_vector(t_vector vect, float scale)
{
	vect.x *= scale;
	vect.y *= scale;
	vect.z *= scale;
	return (vect);
}

/*
** Returns the symetric of the incident vector (from light to object) around
** the normal on the surface.
*/

t_vector		reflected_vector(t_vector incident, t_vector normal)
{
	float		dot_coeff;
	t_vector	reflected;

	dot_coeff = dot_product(scale_vector(incident, 2), normal);
	reflected = scale_vector(normal, -dot_coeff);
	reflected.x += incident.x;
	reflected.y += incident.y;
	reflected.z += incident.z;
	return (normalize_vector(reflected));
}
