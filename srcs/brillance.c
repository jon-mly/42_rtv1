#include "rtv1.h"

static int		specular_color_coord(float intensity, float distance,
	int obj_color, int light_color)
{
	float		color_value;
	float		distance_factor;
	float		k;

	distance_factor = 0.02 * pow((float)(distance / 1.3), (float)2) + 1;
	k = intensity / distance_factor;
	color_value = ((float)obj_color + (float)light_color) * k;
	color_value = fmax(fmin(color_value, 255), 0);
	return ((int)color_value);
}

t_color			specular_light_for_intersection(t_object light_ray,
        t_object ray, t_object object, t_light light)
{
	float		distance;
	float		intensity;
	t_vector	incident;
	t_vector	reflected;
	t_color		specular;

	incident = scale_vector(light_ray.direction, -1);
	distance = points_norm(ray.intersectiion, light_ray.origin) * 0.05;
	reflected = reflected_vector(incident, shape_normal(ray, object));
	intensity = pow(fmax(dot_product(reflected, ray.direction), 0),
        (int)(object.brillance * 100)) * pow(object.brillance, 2);
	specular.r = specular_color_coord(intensity,
        distance, object.color.r, light_ray.color.r);
	specular.g = specular_color_coord(intensity,
        distance, object.color.g, light_ray.color.g);
	specular.b = specular_color_coord(intensity,
        distance, object.color.b, light_ray.color.b);
	specular.a = 0;
	return (specular);
}
