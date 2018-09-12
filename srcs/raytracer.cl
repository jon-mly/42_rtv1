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
	OMNI,
	AMBIANT,
	PROJECTOR
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
	t_vector	horizontal_vect;
	t_vector	vertical_vect;
	float		width;
	float		height;
	float		plane_dist;
	float		horizontal_step;
	float		vertical_step;
	float		x_angle;
	float		y_angle;
	float		z_angle;
}				t_camera;

typedef struct	s_light
{
	t_point			posiition;
	t_vector		direction;
	float			angle;
	t_light_type	typpe;
	t_color			color;
	float			power;
}				t_light;

typedef struct	s_object
{
	t_color			color;
	t_point			center;
	t_point			point;
	t_point			origin;
	t_point			intersectiion;
	t_vector		direction;
	t_vector		normal;
	float			norm;
	float			test;
	float			radius;
	float			angle;
	float			y_angle;
	float			x_angle;
	float				reflection;
	float				diffuse;
	t_object_type	typpe;
	int				intersect;
	char			*name;
}				t_object;

typedef struct	s_scene
{
	t_object	*objects;
	t_light		*lights;
	int			objects_count;
	int			lights_count;
	t_color		theme;
	float		power;
}				t_scene;

int				omni_color_coord(float cosinus, float distance, int obj_color, int light_color);
int             projector_color_coord(float intensity, float distance, int obj_color, int light_color);
t_color			light_for_intersection(t_object light_ray, t_object ray, t_object object, t_light light);
t_object		init_omni_light_ray(t_light light, t_object ray, t_object object);
t_object	init_ambiant_light_ray(t_light light, t_object ray, t_object object);
int				color_to_int(t_color color);
t_color			get_color_on_intersection(t_object ray, global t_object *closest_object, global t_scene *scene, global t_light *light, global t_object *obj);
t_object		intersect_object(t_object ray, t_object object);
t_vector		normalize_vector(t_vector vec);
t_vector		vector_points(t_point p1, t_point p2);
t_object		init_ray(int x, int y, t_camera camera);
t_vector	vect_rotate_x(t_vector vector, float angle, int inverse);
t_vector	vect_rotate_y(t_vector vector, float angle, int inverse);
t_vector	vect_rotate_z(t_vector vector, float angle, int inverse);
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
t_color 	add_color(t_color base, t_color overlay);
int		revert_cone_normal(t_object ray, t_object cone);
int		revert_cylinder_normal(t_object ray, t_object cylinder);
int		revert_sphere_normal(t_object ray, t_object sphere);
int				hit_test(global t_object *clt_obj, global t_object *obj, t_object l_ray, float norm);
t_color			omni_light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light);
t_color			ambiant_light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light);
t_color			ambiant_color(t_scene scene, t_object object);
t_color			projector_light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light);
t_object	init_projector_light_ray(t_light light, t_object ray, t_object object);



/*
** ========== MATHEMATIC HELPERS
*/

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

t_vector	vect_rotate_x(t_vector vector, float angle, int inverse)
{
	t_vector	rotated;

	if (!inverse)
	{
		rotated.x = vector.x;
		rotated.y = vector.y * cos(angle) + vector.z * sin(angle);
		rotated.z = -vector.y * sin(angle) + vector.z * cos(angle);
	}
	else
	{
		rotated.x = vector.x;
		rotated.y = cos(angle) * vector.y - sin(angle) * vector.z;
		rotated.z = sin(angle) * vector.y + cos(angle) * vector.z;
	}
	return (rotated);
}

t_vector	vect_rotate_z(t_vector vector, float angle, int inverse)
{
	t_vector	rotated;

	if (!inverse)
	{
		rotated.x = vector.x * cos(angle) + vector.y * sin(angle);
		rotated.y = -vector.x * sin(angle) + vector.y * cos(angle);
		rotated.z = vector.z;
	}
	else
	{
		rotated.x = cos(angle) * vector.x - sin(angle) * vector.y;
		rotated.y = sin(angle) * vector.x + cos(angle) * vector.y;
		rotated.z = vector.z;
	}
	return (rotated);
}

t_vector	vect_rotate_y(t_vector vector, float angle, int inverse)
{
	t_vector	rotated;

	if (!inverse)
	{
		rotated.x = vector.x * cos(angle) - vector.z * sin(angle);
		rotated.y = vector.y;
		rotated.z = vector.x * sin(angle) + vector.z * cos(angle);
	}
	else
	{
		rotated.x = cos(angle) * vector.x + sin(angle) * vector.z;
		rotated.y = vector.y;
		rotated.z = -sin(angle) * vector.x + cos(angle) * vector.z;
	}
	return (rotated);
}

float		vector_norm(t_vector vec)
{
	float		norm;

	norm = sqrt((float)(pow((float)vec.x, (float)2) + pow((float)vec.y, (float)2) + pow((float)vec.z, (float)2)));
	return (norm);
}

t_vector	rotate_cone_angles(t_object cone, t_vector vect,
			int reverse)
{
	if (!reverse)
	{
		vect = vect_rotate_y(vect, cone.y_angle, reverse);
		vect = vect_rotate_x(vect, cone.x_angle, reverse);
	}
	else
	{
		vect = vect_rotate_x(vect, cone.x_angle, reverse);
		vect = vect_rotate_y(vect, cone.y_angle, reverse);
	}
	return (vect);
}

t_vector	rotate_cylinder_angles(t_object cylinder, t_vector vect,
			int reverse)
{	if (!reverse)
	{
		vect = vect_rotate_y(vect, cylinder.y_angle, reverse);
		vect = vect_rotate_x(vect, cylinder.x_angle, reverse);
	}
	else
	{
		vect = vect_rotate_x(vect, cylinder.x_angle, reverse);
		vect = vect_rotate_y(vect, cylinder.y_angle, reverse);
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

/*
** Solves a quadratic equation but with the aim of returning a distance, which
** has to be a positive value.
** If the value is negative, the equation has no solution.
** Several cases are to be distinguished, in order in the function's body :
** - discriminant < 0 : the ray does not intersect the object
** From this point and for simplication, both x1 and x2 are replaced
** if needed so that x1 <= x2.
** - x1 <= 0 and x2 <= 0 : both intersections are behind the camera,
** so there is no intersection to be represented on screen.
** - x2 > 0 and x1 <= 0 : the camera is inside the object, with one
** point behind the camera, and one in front of it. The one to be
** represented is the one in front of it, so the highest norm
** value.
** - x1 > 0 and x2 > 0 : both intersections are beyond the camera,
** the closest one is to be retained.
*/

float		closest_distance_quadratic(float a, float b, float c)
{
	float		discriminant;
	float		x1;
	float		x2;
	float 		buffer;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	x1 = (-b - sqrt(discriminant)) / (2 * a);
	x2 = (-b + sqrt(discriminant)) / (2 * a);
	if (x2 < x1)
	{
		buffer = x2;
		x2 = x1;
		x1 = buffer;
	}
	if (x1 <= 0 && x2 <= 0)
		return (-1);
	else if (x2 > 0 && x1 <= 0)
		return (x2);
	return (x1);
}


float		points_norm(t_point p1, t_point p2)
{
	float		distance;

	distance = sqrt((float)(pow((float)(p2.x - p1.x), (float)2) + pow((float)(p2.y - p1.y), (float)2) + pow((float)(p2.z - p1.z), (float)2)));
	return (distance);
}


/*
** ========== NORMAL VECTOR CALCULATION
*/

int		revert_cone_normal(t_object ray, t_object cone)
{
	t_vector	light_to_center;
	float		border;
	float		light_distance;

	light_to_center = vector_points(cone.center, ray.origin);
	rotate_cone_angles(cone, light_to_center, 0);
	border = pow((float)light_to_center.z, (float)2) * pow((float)tan(cone.angle), (float)2);
	light_distance = pow((float)light_to_center.x, (float)2) + pow((float)light_to_center.y, (float)2);
	return (light_distance < border);
}

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
	if (points_norm(normal_point, distance) > points_norm(normal_point_2,
				distance))
		normal_point = normal_point_2;
	if (revert_cone_normal(ray, cone))
		normal = vector_points(distance, normal_point);
	else
		normal = vector_points(normal_point, distance);
	normal = rotate_cone_angles(cone, normal, 1);
	return (normalize_vector(normal));
}

int		revert_cylinder_normal(t_object ray, t_object cylinder)
{
	t_vector	light_to_center;
	float		border;
	float		light_distance;

	light_to_center = vector_points(cylinder.point, ray.origin);
	rotate_cylinder_angles(cylinder, light_to_center, 0);
	border = pow(cylinder.radius, 2);
	light_distance = pow(light_to_center.x, 2) + pow(light_to_center.y, 2);
	return (light_distance < border);
}

t_vector		cylinder_normal(t_object ray, t_object cylinder)
{
	t_vector	distance;
	t_point		normal_point;
	t_vector	normal;

	distance = vector_points(cylinder.point, ray.intersectiion);
	distance = rotate_cylinder_angles(cylinder, distance, 0);
	normal_point = (t_point){0, 0, distance.z};
	if (revert_cylinder_normal(ray, cylinder))
		normal = vector_points(distance, normal_point);
	else
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

/*
** Returns true if the origin of the light ray is inside the sphere,
** meaning that only the inner surface is to be enlighted.
*/

int		revert_sphere_normal(t_object ray, t_object sphere)
{
	t_vector	distance_vector;

	distance_vector = vector_points(ray.origin, sphere.center);
	return (vector_norm(distance_vector) < sphere.radius);
}

t_vector		sphere_normal(t_object ray, t_object sphere)
{
	t_vector	normal;

	if (revert_sphere_normal(ray, sphere))
		normal = vector_points(ray.intersectiion, sphere.center);
	else
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



/*
** ========== INTERSECTION POINTS CALCULATION
*/

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



/*
** ========== NORMAL VECTOR CALCULATION
*/

int			color_to_int(t_color color)
{
	int 	r;
	int 	g;
	int		b;
	int 	a;

	r = (int)color.r;
	g = (int)color.g;
	b = (int)color.b;
	a = (int)color.a;
	return (a << 24 | r << 16 | g << 8 | b);
}



/*
** ========== LIGHTING
*/

/*
** A light ray is ignited, beginning from the position of the light itself,
** and directed to the intersection between the initial ray and the closest
** object.
** A base color (shadow color) is given so that, if an object stands
** between the light spot and the intersection, the latter is shadowed.
*/

t_object	init_omni_light_ray(t_light light, t_object ray, t_object object)
{
	t_object		light_ray;
	t_vector	direction;

	light_ray.origin = light.posiition;
	direction = vector_points(light_ray.origin, ray.intersectiion);
	light_ray.norm = vector_norm(direction);
	light_ray.direction = normalize_vector(direction);
	light_ray.intersect = FALSE;
	light_ray.color = color(0, 0, 0, 0);
	return (light_ray);
}

t_object	init_ambiant_light_ray(t_light light, t_object ray, t_object object)
{
	t_object		light_ray;
	t_vector		ray_direction;

	ray_direction = (t_vector){
		.x = -light.direction.x,
		.y = -light.direction.y,
		.z = -light.direction.z,
	};
	light_ray.origin = ray.intersectiion;
	light_ray.direction = ray_direction;
	light_ray.intersect = FALSE;
	light_ray.color = color(0, 0, 0, 0);
	return (light_ray);
}

t_object	init_projector_light_ray(t_light light, t_object ray, t_object object)
{
	t_object		light_ray;
	t_vector	direction;

	light_ray.origin = light.posiition;
	direction = vector_points(light_ray.origin, ray.intersectiion);
	light_ray.norm = vector_norm(direction);
	light_ray.direction = normalize_vector(direction);
	light_ray.intersect = FALSE;
	light_ray.color = color(0, 0, 0, 0);
	return (light_ray);
}


/*
** Supposing there is no object between the light and the intersection, the
** color on this point is calculated, based on the angle between the normal
** of the object on a particular point.
*/

int		omni_color_coord(float cosinus, float distance, int obj_color,
	int light_color)
{
	float	distance_factor;
	float	k;
	float	color_value;

	distance_factor = 0.02 * pow((float)(distance / 1.3), (float)2) + 1;
	k = sqrt(-cosinus) / distance_factor;
	color_value = ((float)obj_color / (4 * distance_factor)) + k * (float)light_color;
	color_value = fmax(fmin((float)color_value, (float)255), 0);
	return ((int)color_value);
}

int		projector_color_coord(float intensity, float distance, int obj_color, int light_color)
{
	float		color_value;
	float		distance_factor;
	float		k;

	distance_factor = 0.02 * pow((float)(distance / 1.3), (float)2) + 1;
	k = intensity / distance_factor;
	color_value = ((float)obj_color + (float)light_color) * k;
	color_value = fmax(fmin((float)color_value, (float)255), 0);
	return ((int)color_value);
}

t_color 	add_color(t_color base, t_color overlay)
{
	t_color 	final;

	final.r = (int)fmin((double)(base.r + overlay.r), (double)255);
	final.g = (int)fmin((double)(base.g + overlay.g), (double)255);
	final.b = (int)fmin((double)(base.b + overlay.b), (double)255);
	final.a = (int)fmin((double)(base.a + overlay.a), (double)255);
	return (final);
}

t_color			ambiant_light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light)
{
	t_color		color;
	float		distance;
	float		cosinus;

	cosinus = dot_product(light_ray.direction, shape_normal(ray, object));
	if (cosinus <= 0)
		return (light_ray.color);
	distance = 100.0 * (100.0 / light.power);
	color.r = omni_color_coord(-cosinus, distance, object.color.r, light.color.r);
	color.g = omni_color_coord(-cosinus, distance, object.color.g, light.color.g);
	color.b = omni_color_coord(-cosinus, distance, object.color.b, light.color.b);
	color.a = 0;
	return (color);
}

t_color			omni_light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light)
{
	t_vector	normal;
	float		cosinus;
	float		distance;
	t_color		color;

	light_ray.intersectiion = ray.intersectiion;
	normal = shape_normal(ray, object);
	if ((object.typpe == CONE || object.typpe == CYLINDER) &&
			dot_product(shape_normal(ray, object),
				shape_normal(light_ray, object)) < 0)
		return ((t_color){0, 0, 0, 0});
	cosinus = dot_product(light_ray.direction, normal);
	if (cosinus >= 0)
		return (light_ray.color);
	distance = points_norm(ray.intersectiion, light_ray.origin);
	color.r = omni_color_coord(cosinus, distance, object.color.r, light.color.r) * object.diffuse;
	color.g = omni_color_coord(cosinus, distance, object.color.g, light.color.g) * object.diffuse;
	color.b = omni_color_coord(cosinus, distance, object.color.b, light.color.b) * object.diffuse;
	color.a = 0;
	return (color);
}

t_color			projector_light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light)
{
	t_vector	normal;
	float		cosinus;
	float		distance;
	float 		intensity;
	t_color		color;

	if (dot_product(light.direction, light_ray.direction) < cos(light.angle))
		return (light_ray.color);
	light_ray.intersectiion = ray.intersectiion;
	normal = shape_normal(ray, object);
	if ((object.typpe == CONE || object.typpe == CYLINDER) &&
			dot_product(shape_normal(ray, object),
				shape_normal(light_ray, object)) < 0)
		return ((t_color){0, 0, 0, 0});
	cosinus = dot_product(light_ray.direction, normal);
	if (cosinus >= 0)
		return (light_ray.color);
	distance = points_norm(ray.intersectiion, light_ray.origin);
	cosinus = dot_product(light.direction, light_ray.direction);
	intensity = cos(2 * acos(cosinus));
	color.r = projector_color_coord(intensity, distance, object.color.r, light.color.r) * object.diffuse;
	color.g = projector_color_coord(intensity, distance, object.color.g, light.color.g) * object.diffuse;
	color.b = projector_color_coord(intensity, distance, object.color.b, light.color.b) * object.diffuse;
	color.a = 0;
	return (color);
}

t_color			light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light)
{
	if (light.typpe == AMBIANT)
		return (ambiant_light_for_intersection(light_ray, ray, object, light));
	else if (light.typpe == PROJECTOR)
		return (projector_light_for_intersection(light_ray, ray, object, light));
	return (omni_light_for_intersection(light_ray, ray, object, light));
}

int				hit_test(global t_object *clt_obj, global t_object *obj, t_object l_ray, float norm)
{
	if (!(l_ray.intersect && l_ray.norm > 0))
		return (0);
	if (clt_obj == obj)
		return (l_ray.norm < norm - 0.1);
	return (l_ray.norm < norm);
}

t_color			ambiant_color(t_scene scene, t_object object)
{
	t_color		ambiant_color;
	float		factor;

	factor = scene.power * object.diffuse;
	ambiant_color.r = factor * (object.color.r * scene.theme.r / 255.0);
	ambiant_color.g = factor * (object.color.g * scene.theme.g / 255.0);
	ambiant_color.b = factor * (object.color.b * scene.theme.b / 255.0);
	ambiant_color.a = 0;
	return (ambiant_color);
}


/*
** For each light, light ray created.
** For each object that is not the intersected one, check if the ray
** intersects with the object. If so, the point on closest_object is shadowed.
** Else, the coloration calculated in the case there is no object in between is
** returned and applied.
*/

t_color			get_color_on_intersection(t_object ray, global t_object *closest_object, global t_scene *scene, global t_light *light, global t_object *obj)
{
	t_object	light_ray;
	int			light_index;
	int			object_index;
	float		norm;
	t_color		coloration;
	int 		is_direct_hit;

	light_index = -1;
	coloration = ambiant_color(*scene, *closest_object);
	while (++light_index < scene->lights_count)
	{
		is_direct_hit = 1;
		if (light[light_index].typpe == OMNI)
			light_ray = init_omni_light_ray(light[light_index], ray, *closest_object);
		else if (light[light_index].typpe == AMBIANT)
			light_ray = init_ambiant_light_ray(light[light_index], ray, *closest_object);
		else if (light[light_index].typpe == PROJECTOR)
			light_ray = init_projector_light_ray(light[light_index], ray, *closest_object);
		norm = light_ray.norm;
		object_index = -1;
		while (++object_index < scene->objects_count && is_direct_hit)
		{
			light_ray = intersect_object(light_ray,
					obj[object_index]);
			if (light[light_index].typpe != AMBIANT && hit_test(closest_object, &obj[object_index], light_ray, norm))
				is_direct_hit = 0;
			else if (light[light_index].typpe == AMBIANT && light_ray.intersect && light_ray.norm > 0.05)
				is_direct_hit = 0;
		}
		if (is_direct_hit)
			coloration = add_color(coloration, light_for_intersection(light_ray, ray, *closest_object, light[light_index]));
	}
	return (coloration);
}

/*
** ========== MAIN FUNCTIONS
*/

t_object		init_ray(int x, int y, t_camera camera)
{
	t_object	ray;
	t_point		projector_point;

	projector_point.x = camera.up_left_corner.x + (double)x * camera.horizontal_vect.x + (double)y * camera.vertical_vect.x;
	projector_point.y = camera.up_left_corner.y + (double)x * camera.horizontal_vect.y + (double)y * camera.vertical_vect.y;
	projector_point.z = camera.up_left_corner.z + (double)x * camera.horizontal_vect.z + (double)y * camera.vertical_vect.z;
	ray.direction = vector_points(camera.spot, projector_point);
	ray.direction = normalize_vector(ray.direction);
	ray.origin = camera.spot;
	ray.intersect = false;
	return (ray);
}

__kernel void				pixel_raytracing_gpu(__write_only image2d_t out, global t_scene *scene, global t_camera *camera, global t_object *obj, global t_light *light)
{
	int					x;
	int					y;
	int					idx;
	t_object			ray;
	int					object_index;
	global t_object	*closest_object;
	int 				closest_object_index;
	float				closest_distance;
	t_color				colorout;

	colorout = (t_color){0, 0, 0, 0};
	x = get_global_id(0);
	y = get_global_id(1);
	idx = get_global_size(0) * get_global_id(1) + get_global_id(0);
	ray = init_ray(x, y, *camera);
	closest_object = NULL;
	closest_object_index = -1;
	object_index = -1;
	while (++object_index < scene->objects_count)
	{
		ray = intersect_object(ray, obj[object_index]);
		if (ray.intersect && ((closest_object_index != -1 && ray.norm < closest_distance) || closest_object_index == -1) && ray.norm > 0)
		{
			closest_object_index = object_index;
			closest_distance = ray.norm;
		}
	}
	if (closest_object_index != -1)
	{
		ray.norm = closest_distance;
		ray.intersectiion.x = ray.origin.x + ray.direction.x * closest_distance;
		ray.intersectiion.y = ray.origin.y + ray.direction.y * closest_distance;
		ray.intersectiion.z = ray.origin.z + ray.direction.z * closest_distance;
		colorout = get_color_on_intersection(ray, &obj[closest_object_index], scene, light, obj);
	}
	write_imagei(out, (int2)(x, y), (int4)(colorout.b, colorout.g, colorout.r, 0));
}
