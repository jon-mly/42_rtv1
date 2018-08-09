# define TRUE 1
# define FALSE 0
# define NULL 0

typedef enum	e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}				t_object_type;

typedef enum	e_light_type
{
	OMNI
}				t_light_type;

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef t_vector	t_point;

typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}				t_color;

typedef struct	s_camera
{
	t_vector	posiition;
	t_vector	direction;
	t_vector	plane;
	t_point		spot;
	t_vector	normal;
	t_vector	up_left_corner;
	float		width;
	float		height;
	float		plane_dist;
	float		horizontal_step;
	float		vertical_step;
	t_vector	horizontal_vect;
	t_vector	vertical_vect;
	float		x_angle;
	float		y_angle;
	float		z_angle;
}				t_camera;

typedef struct	s_light
{
	t_light_type	typpe;
	t_point			posiition;
	t_vector		direction;
	float			angle;
	t_color			color;
}				t_light;

typedef struct	s_object
{
	t_object_type	typpe;
	t_color			color;
	t_point			center;
	t_point			point;
	t_point			origin;
	t_point			intersectiion;
	t_vector		direction;
	t_vector		normal;
	int				intersect;
	float			norm;
	float			radius;
	float			angle;
	float			y_angle;
	float			x_angle;
	char			*name;
}				t_object;

typedef struct	s_scene
{
	t_object	*objects;
	int			objects_count;
	t_light		*lights;
	int			lights_count;
}				t_scene;

int				color_coord(float cosinus, float distance, int obj_color, int light_color);
t_color			light_for_intersection(t_object light_ray, t_object ray, t_object object, t_light light);
t_object		init_light_ray(t_light light, t_object ray, t_object object);
int				color_to_int(t_color color);
t_color			get_color_on_intersection(t_object ray, t_object *closest_object, __global t_scene *scene);
t_object		intersect_object(t_object ray, t_object object);
t_vector		normalize_vector(t_vector vec);
t_vector		vector_points(t_point p1, t_point p2);
t_object		init_ray(int x, int y, t_camera camera);
t_vector		vect_rotate_x(t_vector vec, float angle);
t_vector		vect_rotate_y(t_vector vec, float angle);
float			vector_norm(t_vector vec);
t_vector		rotate_cone_angles(t_object cone, t_vector vect, int revers);
float			dot_product(t_vector vect_1, t_vector vect_2);
float			closest_distance_quadratic(float a, float b, float c);
t_object		cone_intersection(t_object ray, t_object cone);
t_color			color(int r, int g, int b, int a);
t_vector		shape_normal(t_object ray, t_object object);
t_vector		sphere_normal(t_object ray, t_object sphere);
t_vector		plane_normal(t_object ray, t_object plane);
t_vector		cylinder_normal(t_object ray, t_object cylinder);
t_vector		cone_normal(t_object ray, t_object cone);
float			points_norm(t_point p1, t_point p2);
t_vector		rotate_cylinder_angles(t_object cylinder, t_vector vect, int revers);
t_object		sphere_intersection(t_object ray, t_object sphere);
t_object		plane_intersection(t_object ray, t_object plane);
t_object		cylinder_intersection(t_object ray, t_object cylinder);


t_vector		cone_normal(t_object ray, t_object cone)
{
	t_vector	distance;
	float		normal_dist;
	t_point		normal_point;
	t_point		normal_point_2;
	t_vector	normal;

	distance = vector_points(cone.center, ray.intersectiion);
	distance = rotate_cone_angles(cone, distance, 0);
	normal_dist = (cos(cone.angle) + tan(cone.angle) * sin(cone.angle)) *
		vector_norm(distance);
	normal_point = (t_point){0, 0, normal_dist};
	normal_point_2 = (t_point){0, 0, -normal_dist};
	if (points_norm(normal_point, distance) > points_norm(normal_point_2, distance))
		normal_point = normal_point_2;
	normal = vector_points(normal_point, distance);
	normal = rotate_cone_angles(cone, normal, 1);
	return (normalize_vector(normal));
}

t_vector		cylinder_normal(t_object ray, t_object cylinder)
{
	t_vector	distance;
	t_point		normal_point;
	t_vector	normal;

	distance = vector_points(cylinder.point, ray.intersectiion);
	distance = rotate_cylinder_angles(cylinder, distance, 0);
	normal_point = (t_point){0, 0, distance.z};
	normal = vector_points(normal_point, distance);
	normal = rotate_cylinder_angles(cylinder, normal, 1);
	return (normalize_vector(normal));
}

t_vector		plane_normal(t_object ray, t_object plane)
{
	t_vector	normal;

	if (dot_product(ray.direction, plane.normal) <= 0)
		return (normalize_vector(plane.normal));
	normal.x = -(plane.normal.x);
	normal.y = -(plane.normal.y);
	normal.z = -(plane.normal.z);
	return (normalize_vector(normal));
}

t_vector		sphere_normal(t_object ray, t_object sphere)
{
	t_vector	normal;

	normal = vector_points(sphere.center, ray.intersectiion);
	return (normalize_vector(normal));
}

t_vector			shape_normal(t_object ray, t_object object)
{
	if (object.typpe == SPHERE)
		return (sphere_normal(ray, object));
	else if (object.typpe == PLANE)
		return (plane_normal(ray, object));
	else if (object.typpe == CYLINDER)
		return (cylinder_normal(ray, object));
	else
		return (cone_normal(ray, object));
}

t_color		color(int r, int g, int b, int a)
{
	t_color		color;

	color.r = (unsigned char)r;
	color.g = (unsigned char)g;
	color.b = (unsigned char)b;
	color.a = (unsigned char)a;
	return (color);
}

t_vector	normalize_vector(t_vector vec)
{
	float		norm;

	norm = vector_norm(vec);
	vec.x /= norm;
	vec.y /= norm;
	vec.z /= norm;
	return (vec);
}

t_vector	vector_points(t_point p1, t_point p2)
{
	t_vector	vec;

	vec.x = p2.x - p1.x;
	vec.y = p2.y - p1.y;
	vec.z = p2.z - p1.z;
	return (vec);
}

t_object		init_ray(int x, int y, t_camera camera)
{
	t_object	ray;
	t_point		projector_point;

	projector_point.x = camera.up_left_corner.x + (float)x * camera.horizontal_step;
	projector_point.y = camera.up_left_corner.y - (float)y * camera.vertical_step;
	projector_point.z = camera.up_left_corner.z;
	ray.direction = vector_points(camera.spot, projector_point);
	ray.direction = normalize_vector(ray.direction);
	ray.origin = camera.spot;
	ray.intersect = false;
	return (ray);
}

t_vector	vect_rotate_x(t_vector vec, float angle)
{
	t_vector	rotated;

	rotated.x = vec.x;
	rotated.y = vec.y * cos((float)(angle)) + vec.z * sin((float)(angle));
	rotated.z = -vec.y * sin((float)(angle)) + vec.z * cos((float)(angle));
	return (rotated);
}

t_vector	vect_rotate_y(t_vector vec, float angle)
{
	t_vector	rotated;

	rotated.x = vec.x * cos((float)(angle)) - vec.z * sin((float)(angle));
	rotated.y = vec.y;
	rotated.z = vec.x * sin((float)(angle)) + vec.z * cos((float)(angle));
	return (rotated);
}

float		vector_norm(t_vector vec)
{
	float		norm;

	norm = sqrt((float)(pow((float)vec.x, (float)2) + pow((float)vec.y, (float)2) + pow((float)vec.z, (float)2)));
	return (norm);
}

t_vector	rotate_cone_angles(t_object cone, t_vector vect, int revers)
{
	if (!revers)
	{
		vect = vect_rotate_y(vect, -cone.y_angle);
		vect = vect_rotate_x(vect, -cone.x_angle);
	}
	else
	{
		vect = vect_rotate_y(vect, cone.y_angle);
		vect = vect_rotate_x(vect, cone.x_angle);
	}
	return (vect);
}

float		dot_product(t_vector vect_1, t_vector vect_2)
{
	float		product;

	product = (vect_1.x * vect_2.x) +
				(vect_1.y * vect_2.y) +
				(vect_1.z * vect_2.z);
	return (product);
}

float		closest_distance_quadratic(float a, float b, float c)
{
	float		discriminant;
	float		x1;
	float		x2;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	x1 = (-b - sqrt((float)(discriminant))) / (2 * a);
	x2 = (-b + sqrt((float)(discriminant))) / (2 * a);
	if (x1 < 0 && x2 < 0)
		return (-1);
	x1 = fmax((float)x1, (float)0.);
	x2 = fmax((float)x2, (float)0.);
	return (fmin((float)x1, (float)x2));
}

t_vector	rotate_cylinder_angles(t_object cylinder, t_vector vect, int revers)
{
	if (!revers)
	{
		vect = vect_rotate_y(vect, -cylinder.y_angle);
		vect = vect_rotate_x(vect, -cylinder.x_angle);
	}
	else
	{
		vect = vect_rotate_y(vect, cylinder.y_angle);
		vect = vect_rotate_x(vect, cylinder.x_angle);
	}
	return (vect);
}

t_object		cone_intersection(t_object ray, t_object cone)
{
	t_vector	distance;
	t_vector	ray_dir;
	float		a;
	float		b;
	float		c;
	float		k;

	distance = vector_points(cone.center, ray.origin);
	ray_dir = rotate_cone_angles(cone, ray.direction, 0);
	distance = rotate_cone_angles(cone, distance, 0);
	k = -1 - pow((float)(tan((float)(cone.angle))), (float)2);
	a = pow((float)vector_norm(ray_dir), (float)2) + k * pow((float)ray_dir.z, (float)2);
	b = 2 * (dot_product(distance, ray_dir) + k * ray_dir.z * distance.z);
	c = pow((float)vector_norm(distance), (float)2) + k * pow((float)distance.z, (float)2);
	ray.norm = closest_distance_quadratic(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}

t_object	plane_intersection(t_object ray, t_object plane)
{
	if (dot_product(plane.normal, ray.direction) == 0)
	{
		ray.intersect = FALSE;
		return (ray);
	}
	ray.norm = (dot_product(plane.normal, plane.point) - dot_product(plane.normal,
			ray.origin)) / dot_product(plane.normal, ray.direction);
	ray.intersect = (ray.norm > 0 || ray.norm < 10000000);
	return (ray);
}

t_object	sphere_intersection(t_object ray, t_object sphere)
{
	double		a;
	double		b;
	double		c;
	t_vector	distance;

	distance = vector_points(sphere.center, ray.origin);
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(ray.direction, distance);
	c = dot_product(distance, distance) - pow((float)sphere.radius, (float)2);
	ray.norm = closest_distance_quadratic(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}

t_object		cylinder_intersection(t_object ray, t_object cylinder)
{
	t_vector	distance;
	t_vector	ray_dir;
	float		a;
	float		b;
	float		c;

	distance = vector_points(cylinder.point, ray.origin);
	ray_dir = rotate_cylinder_angles(cylinder, ray.direction, 0);
	distance = rotate_cylinder_angles(cylinder, distance, 0);
	a = pow((float)ray_dir.x, (float)2) + pow((float)ray_dir.y, (float)2);
	b = 2 * (distance.x * ray_dir.x + distance.y * ray_dir.y);
	c = pow((float)distance.x, (float)2) + pow((float)distance.y, (float)2) - pow((float)cylinder.radius, (float)2);
	ray.norm = closest_distance_quadratic(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}

t_object			intersect_object(t_object ray, t_object object)
{
	if (object.typpe == SPHERE)
		ray = sphere_intersection(ray, object);
	else if (object.typpe == PLANE)
		ray = plane_intersection(ray, object);
	else if (object.typpe == CYLINDER)
		ray = cylinder_intersection(ray, object);
	else if (object.typpe == CONE)
		ray = cone_intersection(ray, object);
	if (ray.intersect)
	{
		ray.intersectiion.x = ray.origin.x + ray.direction.x * ray.norm;
		ray.intersectiion.y = ray.origin.y + ray.direction.y * ray.norm;
		ray.intersectiion.z = ray.origin.z + ray.direction.z * ray.norm;
	}
	return (ray);
}

int			color_to_int(t_color color)
{
	return ((int)(color.r | color.g << 8 | color.b << 16));
}	

t_object	init_light_ray(t_light light, t_object ray, t_object object)
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

int		color_coord(float cosinus, float distance, int obj_color,
	int light_color)
{
	float	distance_factor;
	float	k;
	float	color_value;

	distance_factor = 0.01 * pow(distance / 1.4, 2) + 1;
	k = cosinus / distance_factor;
	color_value = (float)obj_color / 3 - k * (float)light_color;
	color_value = fmax(fmin(color_value, 255), 0);
	return ((int)color_value);
}

float		points_norm(t_point p1, t_point p2)
{
	float		distance;

	distance = sqrt((float)(pow((float)(p2.x - p1.x), (float)2) + pow((float)(p2.y - p1.y), (float)2) + pow((float)(p2.z - p1.z), (float)2)));
	return (distance);
}

t_color			light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light)
{
	t_vector	normal;
	float		cosinus;
	float		distance;
	t_color		color;

	normal = shape_normal(ray, object);
	cosinus = dot_product(light_ray.direction, normal);
	if (cosinus >= 0)
		return (light_ray.color);
	distance = points_norm(ray.intersectiion, light_ray.origin);
	color.r = color_coord(cosinus, distance, object.color.r, light.color.r);
	color.g = color_coord(cosinus, distance, object.color.g, light.color.g);
	color.b = color_coord(cosinus, distance, object.color.b, light.color.b);
	color.a = 0;
	return (color);
}

t_color			get_color_on_intersection(t_object ray, t_object *closest_object, __global t_scene *scene)
{
	t_object	light_ray;
	int			light_index;
	int			object_index;
	float		norm;
	t_color		coloration;

	light_index = -1;
	coloration = closest_object->color;
	while (++light_index < scene->lights_count)
	{
		light_ray = init_light_ray(((t_light*)(scene->lights))[light_index], ray,
				*closest_object);
		norm = light_ray.norm;
		coloration = light_for_intersection(light_ray, ray, *closest_object,
				(((t_light*)(scene->lights))[light_index]));
		object_index = -1;
		while (++object_index < scene->objects_count)
		{
			if (&(((t_object *)(scene->objects))[object_index]) != closest_object)
			{
				light_ray = intersect_object(light_ray,
						(((t_object *)(scene->objects))[object_index]));
				if (light_ray.intersect && light_ray.norm < norm &&
						light_ray.norm > 0)
					return (light_ray.color);
			}
		}
	}
	return (coloration);
}

__kernel void				pixel_raytracing_gpu(__global int *out, __global t_scene *scene, __global t_camera *camera)
{
	int					x;
	int					y;
	int					idx;
	t_object			ray;
	int					object_index;
	t_object			*closest_object;
	float				closest_distance;

	x = get_global_id(0);
	y = get_global_id(1);
	idx = get_global_size(0) * get_global_id(1) + get_global_id(0);
	ray = init_ray(x, y, *camera);
	closest_object = NULL;
	object_index = -1;
	while (++object_index < scene->objects_count)
	{
		ray = intersect_object(ray, scene->objects[object_index]);
		if (ray.intersect && ((closest_object != NULL && ray.norm < closest_distance) || closest_object == NULL) && ray.norm > 0)
		{
			closest_object = &(((t_object *)(scene->objects))[object_index]);
			closest_distance = ray.norm;
		}
	}
	if (closest_object != NULL)
	{
		ray.norm = closest_distance;
		ray.intersectiion.x = ray.origin.x + ray.direction.x * closest_distance;
		ray.intersectiion.y = ray.origin.y + ray.direction.y * closest_distance;
		ray.intersectiion.z = ray.origin.z + ray.direction.z * closest_distance;
		out[idx] = color_to_int(get_color_on_intersection(ray, closest_object,
			scene));
	}
	else
		out[idx] = 0x00000000;
}
