#include "rtv1.h"

double		vector_norm(t_vector vector)
{
	double		norm;

	norm = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
	return (norm);
}

double		dot_product(t_vector vect_1, t_vector vect_2)
{
	double		product;

	product = (vect_1.x * vect_2.x) +
				(vect_1.y * vect_2.y) +
				(vect_1.z * vect_2.z);
	return (product);
}

t_vector	normalize_vector(t_vector vector)
{
	double		norm;

	norm = vector_norm(vector);
	vector.x /= norm;
	vector.y /= norm;
	vector.z /= norm;
	return (vector);
}

double		quadratic_discriminant(double a, double b, double c)
{
	double		discriminant;

	discriminant = pow(b, 2) - 4 * a * c;
	return (discriminant);
}
