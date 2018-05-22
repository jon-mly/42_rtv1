/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:40 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/05/22 15:05:30 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_ray	init_light_ray(t_light light, t_ray ray, t_object object)
{
	t_ray		light_ray;
	t_vector	direction;

	light_ray.origin = light.position;
	direction = vector_points(light_ray.origin, ray.intersection);
	light_ray.norm = vector_norm(direction);
	light_ray.direction = normalize_vector(direction);
	light_ray.intersect = FALSE;
	light_ray.color = color(object.color.r / 5, object.color.g / 5, object.color.b / 5, 0);
	return (light_ray);
}

static t_color	light_for_intersection(t_ray light_ray, t_ray ray, t_object
	object, t_light light)
{
	t_vector	normal;
	double		cosinus;
	t_color		color;

	normal = shape_normal(ray, object);
	cosinus = dot_product(light_ray.direction, normal);
	if (cosinus >= 0)
		return (light_ray.color);
	color.r = (int)(fmax(fmin((double)object.color.r / (3) - cosinus * (double)light.color.r / 2, 255), 0));
	color.g = (int)(fmax(fmin((double)object.color.g / (3) - cosinus * (double)light.color.g / 2, 255), 0));
	color.b = (int)(fmax(fmin((double)object.color.b / (3) - cosinus * (double)light.color.b / 2, 255), 0));
	color.a = 0;
	return (color);
}

t_color			get_color_on_intersection(t_ray ray, t_object *closest_object,
	t_env *env)
{
	t_ray		light_ray;
	int			light_index;
	int			object_index;
	double		norm;
	t_color		coloration;

	light_index = -1;
	while (++light_index < env->scene.lights_count)
	{
		light_ray = init_light_ray(env->scene.lights[light_index], ray,
				*closest_object);
		norm = light_ray.norm;
		coloration = light_for_intersection(light_ray, ray, *closest_object,
				env->scene.lights[light_index]);
		object_index = -1;
		// Each object of the scene is tested to check if it stands between
		// the light source and the closest object relative to the camera.
		while (++object_index < env->scene.objects_count)
		{
			if (&(env->scene.objects[object_index]) != closest_object)
			{
				light_ray = intersect_object(light_ray,
						env->scene.objects[object_index]);
				// If the light ray interesct with an object before reaching
				// the object we want to calculate the light for, it means that
				// the initial object is shadowed.
				if (light_ray.intersect == TRUE && light_ray.norm < norm &&
						light_ray.norm > 0)
					return (light_ray.color);
			}
		}
	}
	return (coloration);
}
