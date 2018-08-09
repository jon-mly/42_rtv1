typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef t_vector	t_point;

typedef struct	s_camera
{
	t_vector	position;
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
}				t_camera;

typedef struct	s_scene
{
	t_object	*objects;
	int			objects_count;
	t_light		*lights;
	int			lights_count;
}				t_scene;

typedef struct	s_object
{
	t_object_type	type;
	t_color			color;
	t_point			center;
	t_point			point;
	t_point			origin;
	t_point			intersecction;
	t_vector		direction;
	t_vector		normal;
	t_scene			scene;
	t_camera		camera;
	int				intersect;
	float			norm;
	float			radius;
	float			angle;
	float			y_angle;
	float			x_angle;
	void			object;
}				t_object;

typedef struct	s_env
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	unsigned char	*img_str;
	int				win_height;
	int				win_width;
	int				img_height;
	int				img_width;
	int				line_size;
	int				bpp;
	int				endian;
	t_scene			scene;
	t_camera		camera;
	t_object		object;
}				t_env;


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
	ray.direction = normalize(ray.direction);
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

	norm = sqrt((float)(pow((float)(vec.x, 2)) + pow((float)(vec.y, 2)) + pow((float)(vec.z, 2))));
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

t_vector	rotate_cylinder_angles(t_object cylinder, t_vector vect,
			int revers)
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
	k = -1 - pow((float)(tan((float)(cone.angle)), (float)2));
	a = pow((float)vector_norm(ray_dir), (float)2) + k * pow((float)ray_dir.z, (float)2);
	b = 2 * (dot_product(distance, ray_dir) + k * ray_dir.z * distance.z);
	c = pow((float)vector_norm(distance), (float)2) + k * pow((float)distance.z, (float)2);
	ray.norm = closest_distance_quadratic(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}

t_object	plane_intersection(t_object ray, t_object plane)
{
	float			norm;

	if (dot_product(plane.normal, ray.direction) == 0)
	{
		ray.intersect = FALSE;
		return (ray);
	}
	ray.norm = (dot_product(plane.normal, plane.point) - dot_product(plane.normal,
	ray.intersect = (ray.norm > 0 || ray.norm < 10000000);
	return (ray);
}

t_object	sphere_intersection(t_object ray, t_object sphere)
{
	double		a;
	double		b;
	double		c;
	double		discriminant;
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
	float		discriminant;

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
	if (object.type == SPHERE)
		ray = sphere_intersection(ray, *((t_object*)(object.object)));
	else if (object.type == PLANE)
		ray = plane_intersection(ray, *((t_object*)(object.object)));
	else if (object.type == CYLINDER)
		ray = cylinder_intersection(ray, *((t_object*)(object.object)));
	else if (object.type == CONE)
		ray = cone_intersection(ray, *((t_object*)(object.object)));
	if (ray.intersect)
	{
		ray.intersecction.x = ray.origin.x + ray.direction.x * ray.norm;
		ray.intersecction.y = ray.origin.y + ray.direction.y * ray.norm;
		ray.intersecction.z = ray.origin.z + ray.direction.z * ray.norm;
	}
	return (ray);
}

__kernel void				pixel_raytracing_gpu(__global int *out, __global t_env *env, __global t_obj *obj, __global t_light *light)
{
	int			x;
	int			y;
	int			idx;
	t_object		ray;
	int			object_index;
	__global t_object		*closest_object;
	float		closest_distance;

	x = get_global_id(0);
	y = get_global_id(1);
	idx = get_global_size(0) * get_global_id(1) + get_global_id(0);
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
		ray.intersecction.x = ray.origin.x + ray.direction.x * closest_distance;
		ray.intersecction.y = ray.origin.y + ray.direction.y * closest_distance;
		ray.intersecction.z = ray.origin.z + ray.direction.z * closest_distance;
		out[idx] = get_color_on_intersection(ray, closest_object,
			env);
	}
	else
		out[idx] = color(0, 0, 0, 0);
}
