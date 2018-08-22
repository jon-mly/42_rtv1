/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:40 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/08/21 15:20:57 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** A light ray is ignited, beginning from the position of the light itself,
** and directed to the intersection between the initial ray and the closest
** object.
** A base color (shadow color) is given so that, if an object stands
** between the light spot and the intersection, the latter is shadowed.
*/

static t_object	init_light_ray(t_light light, t_object ray, t_object object)
{
	t_object		light_ray;
	t_vector	direction;

	light_ray.origin = light.posiition;
	direction = vector_points(light_ray.origin, ray.intersectiion);
	light_ray.norm = vector_norm(direction);
	light_ray.direction = normalize_vector(direction);
	light_ray.intersect = FALSE;
	light_ray.color = color(object.color.r / 4, object.color.g / 4, object.color.b / 4, 0);
	return (light_ray);
}

/*
** Supposing there is no object between the light and the intersection, the
** color on this point is calculated, based on the angle between the normal
** of the object on a particular point.
*/

static int		color_coord(float cosinus, float distance, int obj_color,
	int light_color)
{
	float	distance_factor;
	float	k;
	float	color_value;

	distance_factor = 0.01 * pow(distance / 1.3, 2) + 1;
	k = cosinus / distance_factor;
	color_value = (float)obj_color / 4 - k * (float)light_color;
	color_value = fmax(fmin(color_value, 255), 0);
	return ((int)color_value);
}

static t_color	light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light)
{
	t_vector	normal;
	float		cosinus;
	float		distance;
	t_color		color;

	normal = shape_normal(ray, object);
	cosinus = dot_product(light_ray.direction, normal);
	// if angle is higher than +/-PI/2, the point is shadowed whatsoever.
	if (cosinus >= 0)
		return (light_ray.color);
	distance = points_norm(ray.intersectiion, light_ray.origin);
	color.r = color_coord(cosinus, distance, object.color.r, light.color.r);
	color.g = color_coord(cosinus, distance, object.color.g, light.color.g);
	color.b = color_coord(cosinus, distance, object.color.b, light.color.b);
	color.a = 0;
	return (color);
}

static t_color 	add_color(t_color base, t_color overlay)
{
	t_color 	final;

	final.r = (int)fmin((double)(base.r + overlay.r), (double)255);
	final.g = (int)fmin((double)(base.g + overlay.g), (double)255);
	final.b = (int)fmin((double)(base.b + overlay.b), (double)255);
	final.a = (int)fmin((double)(base.a + overlay.a), (double)255);
	return (final);
}

/*
** For each light (FIXME: multi-spots not supported so far), light ray created.
** For each object that is not the intersected one, check if the ray
** intersects with the object. If so, the point on closest_object is shadowed.
** Else, the coloration calculated in the case there is no object in between is
** returned and applied.
*/

t_color			get_color_on_intersection(t_object ray, t_object *closest_object,
	t_env *env)
{
	t_object		light_ray;
	int			light_index;
	int			object_index;
	float		norm;
	t_color		coloration;
	int 		is_direct_hit;

	light_index = -1;
	coloration = color(closest_object->color.r / 4, closest_object->color.g / 4, closest_object->color.b / 4, 0);
	while (++light_index < env->scene.lights_count)
	{
		is_direct_hit = 1;
		light_ray = init_light_ray(((t_light*)(env->scene.lights))[light_index], ray,
				*closest_object);
		norm = light_ray.norm;
		object_index = -1;
		while (++object_index < env->scene.objects_count)
		{
			if (&(((t_object *)(env->scene.objects))[object_index]) != closest_object)
			{
				light_ray = intersect_object(light_ray,
						(((t_object *)(env->scene.objects))[object_index]));
				if (light_ray.intersect && light_ray.norm < norm &&
						light_ray.norm > 0)
					is_direct_hit = 0;
			}
		}
		if (is_direct_hit)
			coloration = add_color(coloration, light_for_intersection(light_ray, ray, *closest_object,
				(((t_light*)(env->scene.lights))[light_index])));
	}
	return (coloration);
}
