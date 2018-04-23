#include "rtv1.h"

t_vector	vector(double x, double y, double z)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_point		point(double x, double y, double z)
{
	t_point		point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_pixel		pixel(int x, int y)
{
	t_pixel		pixel;

	pixel.x = x;
	pixel.y = y;
	return (pixel);
}

t_color		color(unsigned char r, unsigned char g, unsigned char b,
	unsigned char a)
{
	t_color		color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}
