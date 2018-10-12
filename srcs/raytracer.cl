# define TRUE 1
# define FALSE 0
# define NULL 0
# define MAX_REFLECTION_ITER 4
# define MAX_REFRACTION_ITER 2
# define ALIASING 2
# define EPSILON 0.02

typedef enum	e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	DISC,
	RECTANGLE,
	TRIANGLE,
	PARALLELOGRAM
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

typedef struct			s_object
{
	t_color				color;
	t_point				center;
	t_point				point;
	t_point				origin;
	t_point				intersectiion;
	t_vector			direction;
	t_vector			normal;
	t_vector			first_vect;
	t_vector			second_vect;
	float				norm;
	float				test;
	float				radius;
	float				angle;
	float				y_angle;
	float				x_angle;
	float				brillance;
	float				diffuse;
	float				reflection;
	float				transparency;
	float				refraction;
	float				height;
	float				width;
	t_object_type		typpe;
	int					intersect;
	int					finite;
	int					covered;
	int					has_density;
	char				*name;
}						t_object;

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
t_color			diffuse_light_for_intersection(t_object light_ray, t_object ray, t_object object, t_light light);
t_object		init_omni_light_ray(t_light light, t_object ray, t_object object);
t_object	init_ambiant_light_ray(t_light light, t_object ray, t_object object);
int				color_to_int(t_color color);
t_color			get_color_on_intersection(t_object ray, global t_object *closest_object, global t_scene *scene, global t_light *light, global t_object *obj);
t_object		intersect_object(t_object ray, t_object object);
t_vector		normalize_vector(t_vector vec);
t_vector		vector_points(t_point p1, t_point p2);
t_object		init_ray(int x, int y, t_camera camera, float aliasing_variation);
t_vector	vect_rotate_x(t_vector vector, float angle, int inverse);
t_vector	vect_rotate_y(t_vector vector, float angle, int inverse);
t_vector	vect_rotate_z(t_vector vector, float angle, int inverse);
float			vector_norm(t_vector vec);
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
t_object		finite_cylinder_intersection(t_object ray, t_object cylinder);
t_object	disc_intersection(t_object ray, t_object disc);
float	farest_distance_quadratic(float a, float b, float c);
t_vector	point_from_vector(t_point origin, t_vector direction, float norm);
t_vector	scale_vector(t_vector vect, float scale);
t_object	finite_cone_intersection(t_object ray, t_object cone);
t_vector		reflected_vector(t_vector incident, t_vector normal);
t_color			specular_light_for_intersection(t_object light_ray, t_object ray,
	t_object object, t_light light);
t_color			raytracing(global t_scene *scene, global t_camera *camera, global t_object *obj, global t_light *light, float aliasing_variation);
t_color		average_color(t_color c1, t_color c2);
int			maximize_color_value(int color_value);
t_vector	rotate_vector_angles(t_object reference, t_vector vect,
			int reverse);
t_object		rectangle_intersection(t_object ray, t_object rectangle);
t_vector	cross_product(t_vector vect_1, t_vector vect_2);
t_object		triangle_intersection(t_object ray, t_object triangle);
t_object		parallelogram_intersection(t_object ray, t_object parallelogram);
t_object		init_reflected_ray(t_object original_ray, t_object intersected_object, float previous_reflection);
t_color			reflected_raytracing(global t_scene *scene, global t_object *obj, global t_light *light,
	t_object ray, t_color colorout);
t_vector		refracted_vector(t_object object, t_object ray, float next_refraction_index);
t_object		init_refracted_ray(t_object original_ray, t_object intersected_object,
	float next_refraction, float next_transparency);
t_color			refracted_raytracing(global t_scene *scene, global t_object *obj, global t_light *light,
	t_object ray);
t_vector	sum_vectors(t_vector vect1, t_vector vect2);





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

t_vector	point_from_vector(t_point origin, t_vector direction, float norm)
{
	t_point		point;

	point.x = origin.x + direction.x * norm;
	point.y = origin.y + direction.y * norm;
	point.z = origin.z + direction.z * norm;
	return (point);
}

t_vector	scale_vector(t_vector vect, float scale)
{
	vect.x *= scale;
	vect.y *= scale;
	vect.z *= scale;
	return (vect);
}

t_vector	sum_vectors(t_vector vect1, t_vector vect2)
{
	t_vector	sum;

	sum.x = vect1.x + vect2.x;
	sum.y = vect1.y + vect2.y;
	sum.z = vect1.z + vect2.z;
	return (sum);
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

t_vector	rotate_vector_angles(t_object reference, t_vector vect,
			int reverse)
{	if (!reverse)
	{
		vect = vect_rotate_y(vect, reference.y_angle, reverse);
		vect = vect_rotate_x(vect, reference.x_angle, reverse);
	}
	else
	{
		vect = vect_rotate_x(vect, reference.x_angle, reverse);
		vect = vect_rotate_y(vect, reference.y_angle, reverse);
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

t_vector	cross_product(t_vector vect_1, t_vector vect_2)
{
	t_vector	cross;

	cross.x = vect_1.y * vect_2.z - vect_1.z * vect_2.y;
	cross.y = vect_1.z * vect_2.x - vect_1.x * vect_2.z;
	cross.z = vect_1.x * vect_2.y - vect_1.y * vect_2.x;
	return (cross);
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

float	farest_distance_quadratic(float a, float b, float c)
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
	return (x2);
}


float		points_norm(t_point p1, t_point p2)
{
	float		distance;

	distance = sqrt((float)(pow((float)(p2.x - p1.x), (float)2) + pow((float)(p2.y - p1.y), (float)2) + pow((float)(p2.z - p1.z), (float)2)));
	return (distance);
}

int			maximize_color_value(int color_value)
{
	return ((int)(fmax(fmin((float)color_value, (float)255), 0)));
	// return ((int)(((1 - exp((float)(-0.0050 * color_value))) * 255)));
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
	rotate_vector_angles(cone, light_to_center, 0);
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
	distance = rotate_vector_angles(cone, distance, 0);
	normal_dist = (cos(cone.angle) + tan(cone.angle) * sin(cone.angle)) *
		vector_norm(distance);
	normal_point = (t_point){0, 0, normal_dist};
	normal_point_2 = (t_point){0, 0, -normal_dist};
	if (points_norm(normal_point, distance) > points_norm(normal_point_2,
				distance))
		normal_point = normal_point_2;
	normal = vector_points(normal_point, distance);
	// if ((!cone.finite || cone.covered) && revert_cone_normal(ray, cone))
	// 	normal = vector_points(distance, normal_point);
	if (dot_product(normalize_vector(normal), rotate_vector_angles(cone, ray.direction, 0)) > 0)
		normal = vector_points(distance, normal_point);
	normal = rotate_vector_angles(cone, normal, 1);
	return (normalize_vector(normal));
}

int		revert_cylinder_normal(t_object ray, t_object cylinder)
{
	t_vector	light_to_center;
	float		border;
	float		light_distance;

	light_to_center = vector_points(cylinder.point, ray.origin);
	rotate_vector_angles(cylinder, light_to_center, 0);
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
	distance = rotate_vector_angles(cylinder, distance, 0);
	normal_point = (t_point){0, 0, distance.z};
	normal = vector_points(normal_point, distance);
	// Could be removed since light inside a cylinder is not to be managed
	// if ((!cylinder.finite || cylinder.covered) && revert_cylinder_normal(ray, cylinder))
	// 	normal = vector_points(distance, normal_point);
	if (dot_product(normalize_vector(normal), rotate_vector_angles(cylinder, ray.direction, 0)) > 0)
		normal = vector_points(distance, normal_point);
	normal = rotate_vector_angles(cylinder, normal, 1);
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
	else if (object.typpe == PLANE || object.typpe == DISC || object.typpe == RECTANGLE
		|| object.typpe == TRIANGLE || object.typpe == PARALLELOGRAM)
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
	ray_dir = rotate_vector_angles(cone, ray.direction, 0);
	distance = rotate_vector_angles(cone, distance, 0);
	k = -1 - pow((float)(tan((float)(cone.angle))), (float)2);
	a = pow((float)vector_norm(ray_dir), (float)2) + k * pow((float)ray_dir.z, (float)2);
	b = 2 * (dot_product(distance, ray_dir) + k * ray_dir.z * distance.z);
	c = pow((float)vector_norm(distance), (float)2) + k * pow((float)distance.z, (float)2);
	ray.norm = closest_distance_quadratic(a, b, c);
	if (ray.norm < EPSILON)
		ray.norm = farest_distance_quadratic(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}

t_object	finite_cone_intersection(t_object ray, t_object cone)
{
	t_vector	distance;
	t_vector	ray_dir;
	float		a;
	float		b;
	float		c;
	float		k;
	float		closest_norm;
	float		farest_norm;

	distance = vector_points(cone.center, ray.origin);
	ray_dir = rotate_vector_angles(cone, ray.direction, 0);
	distance = rotate_vector_angles(cone, distance, 0);
	k = -1 - pow((float)(tan((float)(cone.angle))), (float)2);
	a = pow((float)vector_norm(ray_dir), (float)2) + k * pow((float)ray_dir.z, (float)2);
	b = 2 * (dot_product(distance, ray_dir) + k * ray_dir.z * distance.z);
	c = pow((float)vector_norm(distance), (float)2) + k * pow((float)distance.z, (float)2);
	ray.intersect = FALSE;
	closest_norm = closest_distance_quadratic(a, b, c);
	farest_norm = farest_distance_quadratic(a, b, c);
	if (closest_norm > EPSILON)
	{
		ray.norm = closest_norm;
		ray.intersectiion = point_from_vector(ray.origin, ray.direction, ray.norm);
		distance = vector_points(cone.center, ray.intersectiion);
		distance = rotate_vector_angles(cone, distance, 0);
		ray.intersect = (distance.z >= 0 && distance.z <= cone.height);
	}
	if (!ray.intersect && farest_norm > EPSILON)
	{
		ray.norm = farest_norm;
		ray.intersectiion = point_from_vector(ray.origin, ray.direction, ray.norm);
		distance = vector_points(cone.center, ray.intersectiion);
		distance = rotate_vector_angles(cone, distance, 0);
		ray.intersect = (distance.z >= 0 && distance.z <= cone.height);		
	}
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

t_object	disc_intersection(t_object ray, t_object disc)
{
	ray = plane_intersection(ray, disc);
	if (!ray.intersect)
		return (ray);
	ray.intersectiion = point_from_vector(ray.origin, ray.direction, ray.norm);
	ray.intersect = vector_norm(vector_points(ray.intersectiion, disc.point)) < disc.radius;
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
	ray_dir = rotate_vector_angles(cylinder, ray.direction, 0);
	distance = rotate_vector_angles(cylinder, distance, 0);
	a = pow((float)ray_dir.x, (float)2) + pow((float)ray_dir.y, (float)2);
	b = 2 * (distance.x * ray_dir.x + distance.y * ray_dir.y);
	c = pow((float)distance.x, (float)2) + pow((float)distance.y, (float)2) - pow((float)cylinder.radius, (float)2);
	ray.norm = closest_distance_quadratic(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}

t_object		finite_cylinder_intersection(t_object ray, t_object cylinder)
{
	t_vector	distance;
	t_vector	ray_dir;
	float		a;
	float		b;
	float		c;
	float		closest_norm;
	float		farest_norm;

	distance = vector_points(cylinder.point, ray.origin);
	ray_dir = rotate_vector_angles(cylinder, ray.direction, 0);
	distance = rotate_vector_angles(cylinder, distance, 0);
	a = pow((float)ray_dir.x, (float)2) + pow((float)ray_dir.y, (float)2);
	b = 2 * (distance.x * ray_dir.x + distance.y * ray_dir.y);
	c = pow((float)distance.x, (float)2) + pow((float)distance.y, (float)2) - pow((float)cylinder.radius, (float)2);
	closest_norm = closest_distance_quadratic(a, b, c);
	farest_norm = farest_distance_quadratic(a, b, c);
	ray.intersect = FALSE;
	if (closest_norm > EPSILON)
	{
		ray.norm = closest_norm;
		ray.intersectiion = point_from_vector(ray.origin, ray.direction, ray.norm);
		distance = vector_points(cylinder.point, ray.intersectiion);
		distance = rotate_vector_angles(cylinder, distance, 0);
		ray.intersect = (distance.z >= 0 && distance.z <= cylinder.height);
	}
	if (!ray.intersect && farest_norm > EPSILON)
	{
		ray.norm = farest_norm;
		ray.intersectiion = point_from_vector(ray.origin, ray.direction, ray.norm);
		distance = vector_points(cylinder.point, ray.intersectiion);
		distance = rotate_vector_angles(cylinder, distance, 0);
		ray.intersect = (distance.z >= 0 && distance.z <= cylinder.height);		
	}
	return (ray);
}

t_object		rectangle_intersection(t_object ray, t_object rectangle)
{
	t_vector	intersection_dist;

	ray = plane_intersection(ray, rectangle);
	if (!ray.intersect)
		return (ray);
	ray.intersectiion = point_from_vector(ray.origin, ray.direction, ray.norm);
	intersection_dist = vector_points(rectangle.point, ray.intersectiion);
	intersection_dist = rotate_vector_angles(rectangle, intersection_dist, 0);
	ray.intersect = (intersection_dist.x >= 0 && intersection_dist.z >= 0
		&& intersection_dist.x < rectangle.width && intersection_dist.z < rectangle.height);
	return (ray);
}

t_object		triangle_intersection(t_object ray, t_object triangle)
{
	t_vector	distance;
	float		a;
	float		b;
	float		k;

	distance = vector_points(triangle.point, ray.origin);
	k = -dot_product(cross_product(triangle.second_vect, triangle.first_vect), ray.direction);
	if (k == 0)
		return (ray);
	a = -dot_product(cross_product(distance, triangle.first_vect), ray.direction) / k;
	b = -dot_product(cross_product(triangle.second_vect, distance), ray.direction) / k;
	ray.intersect = (a >= 0 && b >= 0 && a + b < 1);
	ray.norm = dot_product(cross_product(triangle.second_vect, triangle.first_vect), distance) / k;
	return (ray);
}

t_object		parallelogram_intersection(t_object ray, t_object parallelogram)
{
	t_vector	distance;
	float		a;
	float		b;
	float		k;

	distance = vector_points(parallelogram.point, ray.origin);
	k = -dot_product(cross_product(parallelogram.second_vect, parallelogram.first_vect), ray.direction);
	if (k == 0)
		return (ray);
	a = -dot_product(cross_product(distance, parallelogram.first_vect), ray.direction) / k;
	b = -dot_product(cross_product(parallelogram.second_vect, distance), ray.direction) / k;
	ray.intersect = (a >= 0 && b >= 0 && a < 1 && b < 1);
	ray.norm = dot_product(cross_product(parallelogram.second_vect, parallelogram.first_vect), distance) / k;
	// if (ray.intersect)
	// 	printf("%.2f\n", ray.norm);
	return (ray);
}

t_object			intersect_object(t_object ray, t_object object)
{
	if (object.typpe == SPHERE)
		ray = sphere_intersection(ray, object);
	else if (object.typpe == PLANE)
		ray = plane_intersection(ray, object);
	else if (object.typpe == CYLINDER)
		ray = (object.finite) 
			? finite_cylinder_intersection(ray, object) 
			: cylinder_intersection(ray, object);
	else if (object.typpe == CONE)
		ray = (object.finite)
			? finite_cone_intersection(ray, object)
			: cone_intersection(ray, object);
	else if (object.typpe == DISC)
		ray = disc_intersection(ray, object);
	else if (object.typpe == RECTANGLE)
		ray = rectangle_intersection(ray, object);
	else if (object.typpe == TRIANGLE)
		ray = triangle_intersection(ray, object);
	else if (object.typpe == PARALLELOGRAM)
		ray = parallelogram_intersection(ray, object);
	if (ray.intersect)
		ray.intersectiion = point_from_vector(ray.origin, ray.direction, ray.norm);
	return (ray);
}


/*
** ========== SPECULAR VECTOR CALCULATION
*/

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


/*
** ========== REFRACTED VECTOR CALCULATION
*/

/*
** Returns the refracted vector of the ray's direction when hitting the surface
** of the object.
** The initial refraction index is expected to be set in the ray's parameters.
**
** The angle between the normal and the source vector is calculated using the
** oriented angle between the normal (from intersection to outside) and the 
** inverse of the ray's direction, which is originally from outside to the
** intersection.
*/

t_vector		refracted_vector(t_object ray, t_object object, float next_refraction_index)
{
	t_vector	normal;
	t_vector	opposed_direction;
	t_vector	refracted;
	float		incident_cos;
	float		refraction_indexes_ratio;

	normal = shape_normal(ray, object);
	opposed_direction = scale_vector(ray.direction, -1);
	refraction_indexes_ratio = ray.refraction / next_refraction_index;
	if (fabs(refraction_indexes_ratio - 1) < EPSILON)
		return ray.direction;
	incident_cos = 1.0 - pow(refraction_indexes_ratio, 2) * (1.0 - pow(dot_product(normal, ray.direction), 2));
	// incident_cos = pow(dot_product(normal, opposed_direction), 2);
	// printf("ratio : %.2f, cos : %.2f\n", refraction_indexes_ratio, incident_cos);
	// refracted = scale_vector(ray.direction, refraction_indexes_ratio);
	// normal = scale_vector(normal, incident_cos + refraction_indexes_ratio
	// 	* dot_product(ray.direction, normal));
	// refracted.x -= normal.x;
	// refracted.y -= normal.y;
	// refracted.z -= normal.z;
	refracted = scale_vector(ray.direction, refraction_indexes_ratio);
	refracted = sum_vectors(refracted, scale_vector(normal, -1 * refraction_indexes_ratio * dot_product(ray.direction, normal)));
	refracted = sum_vectors(refracted, scale_vector(normal, -1 * sqrt(incident_cos)));
	return (normalize_vector(refracted));
}


/*
** ========== COLORATION TOOL
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
	color_value = ((float)obj_color + (float)light_color) * k;
	color_value = maximize_color_value((int)color_value);
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
	color_value = maximize_color_value((int)color_value);
	return ((int)color_value);
}

t_color 	add_color(t_color base, t_color overlay)
{
	t_color 	final;

	final.r = maximize_color_value(base.r + overlay.r);
	final.g = maximize_color_value(base.g + overlay.g);
	final.b = maximize_color_value(base.b + overlay.b);
	final.a = maximize_color_value(base.a + overlay.a);
	return (final);
}

t_color		average_color(t_color c1, t_color c2)
{
	t_color		final;

	final.r = (c1.r + c2.r) / 2;
	final.g = (c1.g + c2.g) / 2;
	final.b = (c1.b + c2.b) / 2;
	final.a = (c1.a + c2.a) / 2;
	return (final);
}

t_color			ambiant_light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light)
{
	t_color		color;
	float		distance;
	float		cosinus;

	cosinus = dot_product(light_ray.direction, shape_normal(ray, object)) * object.diffuse;
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
	// FIXME: if the ray is from an Ambiant light, as the direction is
	// inverted : from the point to the light, the condition below
	// will be false. Case to handle or remove
	// if ((object.typpe == CONE || object.typpe == CYLINDER) &&
	// 		dot_product(shape_normal(ray, object),
	// 			shape_normal(light_ray, object)) < 0)
	// 	return ((t_color){0, 0, 0, 0});
	cosinus = dot_product(light_ray.direction, normal) * object.diffuse;
	if (cosinus >= 0)
		return (light_ray.color);
	distance = points_norm(ray.intersectiion, light_ray.origin) * (100.0 / light.power);
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
	// if ((object.typpe == CONE || object.typpe == CYLINDER) &&
	// 		dot_product(shape_normal(ray, object),
	// 			shape_normal(light_ray, object)) < 0)
	// 	return ((t_color){0, 0, 0, 0});
	distance = points_norm(ray.intersectiion, light_ray.origin) * (100.0 / light.power);
	cosinus = dot_product(light.direction, light_ray.direction);
	intensity = (1 / (1 - cos(light.angle))) * cosinus - (cos(light.angle) / (1 - cos(light.angle)));
	intensity *= object.diffuse;
	cosinus = dot_product(light_ray.direction, normal);
	if (cosinus >= 0)
		return (light_ray.color);
	intensity = -cosinus * intensity;
	color.r = projector_color_coord(intensity, distance, object.color.r, light.color.r) * object.diffuse;
	color.g = projector_color_coord(intensity, distance, object.color.g, light.color.g) * object.diffuse;
	color.b = projector_color_coord(intensity, distance, object.color.b, light.color.b) * object.diffuse;
	color.a = 0;
	return (color);
}

t_color			diffuse_light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light)
{
	if (light.typpe == AMBIANT)
		return (ambiant_light_for_intersection(light_ray, ray, object, light));
	else if (light.typpe == PROJECTOR)
		return (projector_light_for_intersection(light_ray, ray, object, light));
	return (omni_light_for_intersection(light_ray, ray, object, light));
}

t_color			specular_light_for_intersection(t_object light_ray, t_object ray,
	t_object object, t_light light)
{
	float		distance;
	float		intensity;
	t_vector	incident;
	t_vector	reflected;
	t_color		specular;

	if (light.typpe == PROJECTOR && dot_product(light_ray.direction, light.direction) < cos(light.angle))
		return (color(0, 0, 0, 0));
	incident = (light.typpe != AMBIANT) ? scale_vector(light_ray.direction, -1) : light_ray.direction;
	distance = (light.typpe != AMBIANT)
		? points_norm(ray.intersectiion, light_ray.origin) * (100.0 / light.power)
		: 100.0 * (100.0 / light.power);
		distance = 1;
	reflected = reflected_vector(incident, shape_normal(ray, object));
	intensity = pow(fmax(dot_product(reflected, ray.direction), 0), (int)(object.brillance * 100)) * object.brillance;
	if (light.typpe == PROJECTOR)
		intensity *= (1 / (1 - cos(light.angle))) * dot_product(light.direction, light_ray.direction) - (cos(light.angle) / (1 - cos(light.angle)));
	// printf("intensity : %.2f\n", intensity);
	specular.r = projector_color_coord(intensity, distance, object.color.r, light.color.r);
	specular.g = projector_color_coord(intensity, distance, object.color.g, light.color.g);
	specular.b = projector_color_coord(intensity, distance, object.color.b, light.color.b);
	specular.a = 0;
	return (specular);
}


int				hit_test(global t_object *clt_obj, global t_object *obj, t_object l_ray, float norm)
{
	if (!(l_ray.intersect && l_ray.norm > EPSILON))
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
			else if (light[light_index].typpe == AMBIANT && light_ray.intersect)
			{
				if (closest_object == &obj[object_index] && light_ray.norm > EPSILON)
					is_direct_hit = 0;
				else if (closest_object != &obj[object_index] && light_ray.norm > 0)
					is_direct_hit = 0;
			}
		}
		if (is_direct_hit)
		{
			coloration = add_color(coloration, diffuse_light_for_intersection(light_ray, ray, *closest_object, light[light_index]));
			coloration = add_color(coloration, specular_light_for_intersection(light_ray, ray, *closest_object, light[light_index]));
		}
	}
	return (coloration);
}

/*
** ==================================================================
** INTERSECTION
** ==================================================================
*/

/*
** ========== REFRACTED LIGHT
*/

t_object		init_refracted_ray(t_object original_ray, t_object intersected_object,
	float next_refraction, float next_transparency)
{
	t_object		ray;

	// printf("original : %.2f, %.2f, %.2f\n", original_ray.direction.x, original_ray.direction.y, original_ray.direction.z);
	ray.norm = -1;
	ray.direction = refracted_vector(original_ray, intersected_object, next_refraction);
		// printf("%.2f, %.2f, %.2f\n", ray.direction.x, ray.direction.y, ray.direction.z);
	// ray.origin = original_ray.intersectiion;
	ray.origin = point_from_vector(original_ray.intersectiion, ray.direction, EPSILON);
	ray.intersect = FALSE;
	// FIXME: this is essentially wrong
	ray.transparency = next_transparency;
	ray.refraction = next_refraction;
	return (ray);
}

t_color			refracted_raytracing(global t_scene *scene, global t_object *obj, global t_light *light,
	t_object ray)
{
	int					object_index;
	int 				closest_object_index;
	float				closest_distance;
	t_color				added_color;
	t_color				colorout;
	int					iter_count;

	iter_count = -1;
	colorout = color(0, 0, 0, 0);
	while (++iter_count < MAX_REFRACTION_ITER) {
		added_color = color(0, 0, 0, 0);
		closest_object_index = -1;
		object_index = -1;
		while (++object_index < scene->objects_count)
		{
			// Looks like there is no intersection with the ray, while the ray.direction is
			// set to be the same as the original ray (since in the current test the
			// refraction index is 1).
			ray = intersect_object(ray, obj[object_index]);
			if (ray.intersect && ((closest_object_index != -1 && ray.norm < closest_distance) || closest_object_index == -1) && ray.norm > EPSILON)
			{
				closest_object_index = object_index;
				closest_distance = ray.norm;
			}
		}
		// Test : only the ray that touches a new object produces light.
		// Supposes that once inside an object, the ray will only touch
		// the other side of the same object.
		if (closest_object_index != -1 && iter_count % 2 == 1)
		{
			ray.norm = closest_distance;
			ray.intersectiion = point_from_vector(ray.origin, ray.direction, closest_distance);
			// printf("%s\n", obj[closest_object_index].name);
			added_color = get_color_on_intersection(ray, &obj[closest_object_index], scene, light, obj);
			// printf("Added : %d, %d, %d\n", added_color.r, added_color.g, added_color.b);
			// added_color.r *= ray.transparency;
			// added_color.g *= ray.transparency;
			// added_color.b *= ray.transparency;
			// added_color.a *= ray.transparency;
		}
		else
			return (colorout);
		colorout = add_color(colorout, added_color);
		if (iter_count % 2 == 1)
			ray = init_refracted_ray(ray, obj[closest_object_index],
				1, 1);
		else
			ray = init_refracted_ray(ray, obj[closest_object_index],
				obj[closest_object_index].refraction, obj[closest_object_index].transparency);
	}
	// printf("%d, %d, %d\n", colorout.r, colorout.g, colorout.b);
	// return (color(0, 0, 255, 0));
	return (colorout);
}

/*
** ========== REFLECTED LIGHT
*/

t_object		init_reflected_ray(t_object original_ray, t_object intersected_object, float previous_reflection)
{
	t_object	ray;

	ray.direction = reflected_vector(original_ray.direction, shape_normal(original_ray, intersected_object));
	ray.direction = normalize_vector(ray.direction);
	// ray.origin = original_ray.intersectiion;
	ray.origin = point_from_vector(original_ray.intersectiion, ray.direction, EPSILON);
	ray.intersect = FALSE;
	ray.reflection = intersected_object.reflection * previous_reflection;
	return (ray);
}

t_color			reflected_raytracing(global t_scene *scene, global t_object *obj, global t_light *light,
	t_object ray, t_color colorout)
{
	int					object_index;
	int 				closest_object_index;
	float				closest_distance;
	t_color				added_color;
	int					iter_count;

	iter_count = -1;
	while (++iter_count < MAX_REFLECTION_ITER) {
		added_color = color(0, 0, 0, 0);
		closest_object_index = -1;
		object_index = -1;
		while (++object_index < scene->objects_count)
		{
			ray = intersect_object(ray, obj[object_index]);
			if (ray.intersect && ((closest_object_index != -1 && ray.norm < closest_distance) || closest_object_index == -1) && ray.norm > EPSILON)
			{
				closest_object_index = object_index;
				closest_distance = ray.norm;
			}
		}
		if (closest_object_index != -1)
		{
			ray.norm = closest_distance;
			ray.intersectiion = point_from_vector(ray.origin, ray.direction, closest_distance);
			added_color = get_color_on_intersection(ray, &obj[closest_object_index], scene, light, obj);
			added_color.r *= ray.reflection;
			added_color.g *= ray.reflection;
			added_color.b *= ray.reflection;
			added_color.a *= ray.reflection;
		}
		// FIXME : what happens if closets_object_index equals -1 here ?
		// else
		// 		return (colorout);
		colorout = add_color(colorout, added_color);
		ray = init_reflected_ray(ray, obj[closest_object_index], ray.reflection);
	}
	return (colorout);
}

/*
** ========== INITIAL INTERSECTION
*/

t_object		init_ray(int x, int y, t_camera camera, float aliasing_variation)
{
	t_object	ray;
	t_point		projector_point;
	double			virtual_x;
	double			virtual_y;			

	virtual_x = (double)x + aliasing_variation;
	virtual_y = (double)y + aliasing_variation;
	projector_point.x = camera.up_left_corner.x + virtual_x * camera.horizontal_vect.x + virtual_y * camera.vertical_vect.x;
	projector_point.y = camera.up_left_corner.y + virtual_x * camera.horizontal_vect.y + virtual_y * camera.vertical_vect.y;
	projector_point.z = camera.up_left_corner.z + virtual_x * camera.horizontal_vect.z + virtual_y * camera.vertical_vect.z;
	ray.direction = vector_points(camera.spot, projector_point);
	ray.direction = normalize_vector(ray.direction);
	ray.origin = camera.spot;
	ray.refraction = 1;
	ray.intersect = FALSE;
	return (ray);
}

t_color			raytracing(global t_scene *scene, global t_camera *camera, global t_object *obj, global t_light *light, float aliasing_variation)
{
	int					x;
	int					y;
	int					idx;
	t_object			ray;
	int					object_index;
	int 				closest_object_index;
	float				closest_distance;
	t_color				colorout;

	colorout = (t_color){0, 0, 0, 0};
	x = get_global_id(0);
	y = get_global_id(1);
	idx = get_global_size(0) * get_global_id(1) + get_global_id(0);
	ray = init_ray(x, y, *camera, aliasing_variation);
	closest_object_index = -1;
	object_index = -1;
	while (++object_index < scene->objects_count)
	{
		if (x == 0 && y == 0)
			printf("%s : %.2f\n", obj[object_index].name, obj[object_index].transparency);
		ray = intersect_object(ray, obj[object_index]);
		if (ray.intersect && ((closest_object_index != -1 && ray.norm < closest_distance) || closest_object_index == -1) && ray.norm > EPSILON)
		{
			closest_object_index = object_index;
			closest_distance = ray.norm;
		}
	}
	if (closest_object_index != -1)
	{
		ray.norm = closest_distance;
		ray.intersectiion = point_from_vector(ray.origin, ray.direction, closest_distance);
		colorout = get_color_on_intersection(ray, &obj[closest_object_index], scene, light, obj);
		if (obj[closest_object_index].reflection > 0)
			colorout = add_color(colorout, reflected_raytracing(scene, obj, light,
				init_reflected_ray(ray, obj[closest_object_index], 1), color(0, 0, 0, 0)));
		if (obj[closest_object_index].transparency > 0)
			colorout = add_color(colorout, refracted_raytracing(scene, obj, light,
				init_refracted_ray(ray, obj[closest_object_index],
					obj[closest_object_index].refraction, 1)));
	}
	return (colorout);
}

/*
** ========== MAIN FUNCTION
*/

__kernel void				pixel_raytracing_gpu(__write_only image2d_t out, global t_scene *scene, global t_camera *camera, global t_object *obj, global t_light *light)
{
	int					x;
	int					y;
	int			aliasing_iter;
	float		aliasing_variation;
	t_color		average;

	x = get_global_id(0);
	y = get_global_id(1);
	aliasing_iter = -1;
	//TODO: set aliasing value into scene
	while (++aliasing_iter < ALIASING)
	{
		aliasing_variation = (double)aliasing_iter / (double)ALIASING;
		if (aliasing_iter == 0)
			average = raytracing(scene, camera, obj, light, aliasing_variation);
		else
			average = average_color(average, raytracing(scene, camera, obj, light, aliasing_variation));
	}
	write_imagei(out, (int2)(x, y), (int4)(average.b, average.g, average.r, 0));
}
