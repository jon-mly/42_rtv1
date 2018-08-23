#include "rtv1.h"

static t_object	debug_init_light_ray(t_light light, t_object ray, t_object object)
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

static int		debug_color_coord(float cosinus, float distance, int obj_color,
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

static t_color	debug_light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light)
{
	t_vector	normal;
	float		cosinus;
	float		distance;
	t_color		color;

	normal = shape_normal(ray, object);
	printf("Normal ray   = %.2f, %.2f, %.2f\n", normal.x, normal.y, normal.z);
	light_ray.intersectiion = ray.intersectiion;
	normal = shape_normal(light_ray, object);
	printf("Normal light = %.2f, %.2f, %.2f\n", normal.x, normal.y, normal.z);
	cosinus = dot_product(ray.direction, normal);
	if (cosinus >= 0)
		return (light_ray.color);
	cosinus = dot_product(light_ray.direction, normal);
	// if angle is higher than +/-PI/2, the point is shadowed whatsoever.
	if (cosinus >= 0)
		return (light_ray.color);
	distance = points_norm(ray.intersectiion, light_ray.origin);
	color.r = debug_color_coord(cosinus, distance, object.color.r, light.color.r);
	color.g = debug_color_coord(cosinus, distance, object.color.g, light.color.g);
	color.b = debug_color_coord(cosinus, distance, object.color.b, light.color.b);
	color.a = 0;
	return (color);
}

static t_color 	debug_add_color(t_color base, t_color overlay)
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

static t_color			debug_get_color_on_intersection(t_object ray, t_object *closest_object,
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
		light_ray = debug_init_light_ray(((t_light*)(env->scene.lights))[light_index], ray,
				*closest_object);
		norm = light_ray.norm;
		object_index = -1;
		while (++object_index < env->scene.objects_count && is_direct_hit)
		{
			// if (&(((t_object *)(env->scene.objects))[object_index]) != closest_object)
			// {
				light_ray = intersect_object(light_ray,
						(((t_object *)(env->scene.objects))[object_index]));
				if (light_ray.intersect && light_ray.norm - norm < - 0.05 &&
						light_ray.norm > 0)
				{
					is_direct_hit = 0;
					printf("Has hit %s\n", (((t_object *)(env->scene.objects))[object_index]).name);
				}
			// }
		}
		printf("Is direct hit ? %d\n", is_direct_hit);
		if (is_direct_hit)
			coloration = debug_add_color(coloration, debug_light_for_intersection(light_ray, ray, *closest_object,
				(((t_light*)(env->scene.lights))[light_index])));
	}
	return (coloration);
}


void	debug_raytracing(int x, int y, t_env *env)
{
	t_object		ray;
	int			object_index;
	t_object	*closest_object;
	float		closest_distance;

	ray = init_ray(x, y, env->camera);
	closest_object = NULL;
	object_index = -1;
	while (++object_index < env->scene.objects_count)
	{
		ray = intersect_object(ray, env->scene.objects[object_index]);
		if (ray.intersect && ((closest_object != NULL && ray.norm < closest_distance) || closest_object == NULL) && ray.norm > 0)
		{
			closest_object = &(env->scene.objects[object_index]);
			closest_distance = ray.norm;
		}
	}
	if (closest_object != NULL)
	{
		ray.norm = closest_distance;
		ray.intersectiion.x = ray.origin.x + ray.direction.x * closest_distance;
		ray.intersectiion.y = ray.origin.y + ray.direction.y * closest_distance;
		ray.intersectiion.z = ray.origin.z + ray.direction.z * closest_distance;
		printf("Closest object at %.2f, named %s\n", ray.norm, closest_object->name);
		debug_get_color_on_intersection(ray, closest_object, env);
	}
}

int		debug_mouse_event(int event, int x, int y, void *param)
{
	t_env *env;

	env = (t_env*)param;
	if (event != 1)
		return 0;
	debug_raytracing(x, y, env);
	return 0;
}
