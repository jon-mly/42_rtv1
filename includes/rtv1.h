/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:37:32 by aabelque          #+#    #+#             */
/*   Updated: 2018/09/10 17:43:32 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

/*
** ====== includes
*/

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <math.h>

# ifdef __APPLE__
#  include <OpenCL/cl.h>
# else
#  include <CL/cl.h>
# endif

/*
** ======= macros
*/

# define WIN_HEIGHT 1000
# define WIN_WIDTH 1500
# define FOV 0.40

# define KEY_ESC 53

# define TRUE 1
# define FALSE 0

/*
** ======= enumerations
*/

typedef enum			e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	DISC,
	RECTANGLE,
	TRIANGLE,
	PARALLELOGRAM
}						t_object_type;

typedef enum			e_light_type
{
	OMNI,
	AMBIANT,
	PROJECTOR
}						t_light_type;

/*
** ======= structures
*/

typedef struct			s_pixel
{
	int					x;
	int					y;
}						t_pixel;

typedef struct			s_vector
{
	float				x;
	float				y;
	float				z;
}						t_vector;

typedef t_vector		t_point;

typedef struct			s_color
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
	unsigned char		a;
}						t_color;

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

typedef struct			s_light
{
	t_point				posiition;
	t_vector			direction;
	float				angle;
	t_light_type		typpe;
	t_color				color;
	float				power;
}						t_light;

typedef struct			s_camera
{
	t_vector			posiition;
	t_vector			direction;
	t_vector			discplane;
	t_point				spot;
	t_vector			normal;
	t_vector			up_left_corner;
	t_vector			horizontal_vect;
	t_vector			vertical_vect;
	float				width;
	float				height;
	float				plane_dist;
	float				horizontal_step;
	float				vertical_step;
	float				x_angle;
	float				y_angle;
	float				z_angle;
}						t_camera;

typedef struct			s_scene
{
	t_object			*objects;
	t_light				*lights;
	int					objects_count;
	int					lights_count;
	t_color		theme;
	float		power;
}						t_scene;

typedef	struct			s_opencl
{
	size_t				img_s;
	size_t				imgxy[2];
	size_t				origin[3];
	size_t				region[3];
	int					*bufhst;
	char				*kernel_src;
	cl_device_type		dev_type;
	cl_int				err;
	cl_uint				num_dev;
	cl_mem				input_scene;
	cl_mem				input_cam;
	cl_mem				output;
	cl_mem				structobj;
	cl_mem				structlight;
	cl_platform_id		platform_id;
	cl_image_format		format;
	cl_image_desc		desc;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	commands;
	cl_program			program;
	cl_kernel			kernel;
}						t_opencl;

typedef struct			s_env
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	char				*img_str;
	int					win_height;
	int					win_width;
	int					img_height;
	int					img_width;
	int					line_size;
	int					bpp;
	int					endian;
	int					light_i;
	int					obj_i;
	int					is_direct_hit;
	t_scene				scene;
	t_object			object;
	t_camera			camera;
	t_opencl			opcl;
}						t_env;

/*
** ======= prototypes
*/

int						error_gpu(t_opencl *opcl);
void					opencl_init2(t_opencl *opcl, t_env *e);
void					opencl_draw(t_opencl *opcl, t_env *e);
void					set_opencl_env(t_opencl *opcl);
void					create_kernel(cl_program program,
		cl_kernel *kernel, const char *func);
char					*get_kernel_source(char *file);
void					opencl_init(t_opencl *opcl, t_env *env);
void					create_prog(t_opencl *opcl);
void					exit_error(t_env *env);
void					exit_normally(t_env *env);
void					exit_usage(void);
void					exit_invalid_file(void);
t_env					*init_env(char *file_name);
void					calculate_scene(t_env *env);
t_camera				init_camera(t_env *env);
t_camera				set_camera(int fd, t_env *env);
int						handle_key_event(int key, void *param);
int						expose_event(void *param);
int						exit_properly(void *param);
void					fill_pixel(t_env *env, int x, int y, t_color color);
void					fill_pixel_value(t_env *env, int x,
		int y, int color_value);
t_vector				vector(float x, float y, float z);
t_vector				vector_points(t_point p1, t_point p2);
t_point					point(float x, float y, float z);
t_pixel					pixel(int x, int y);
t_color					color(int r, int g, int b, int a);
float					vector_norm(t_vector vector);
t_vector				normalize_vector(t_vector vector);
float					dot_product(t_vector vect_1, t_vector vect_2);
float					points_norm(t_point p1, t_point p2);
t_object				intersect_object(t_object ray, t_object object);
t_vector				shape_normal(t_object ray, t_object object);
void					pixel_raytracing(int x, int y, t_env *env);
t_scene					get_sample_scene(void);
t_color					get_color_on_intersection(t_object ray,
		t_object *clt_obj, t_env *e);
void					deinit_env(t_env *env);
int						line_len(char **line);
void					clear_line(char **line);
char					**split_new_line(int fd);
t_light					*add_light(int fd, t_light *existing_lights, int count);
t_object				add_new_object(int fd, char *type);
t_scene					create_scene(t_env *env, char *file_name, int fd);
t_object				cylinder_intersection(t_object ray, t_object cylinder);
t_object				cone_intersection(t_object ray, t_object cone,
		t_vector distance);
t_object				plane_intersection(t_object ray, t_object plane);
t_object				sphere_intersection(t_object ray, t_object sphere);
t_vector				cone_normal(t_object ray, t_object cone);
t_vector				cylinder_normal(t_object ray, t_object cylinder);
t_vector				plane_normal(t_object ray, t_object plane);
t_vector				sphere_normal(t_object ray, t_object sphere);
float					degrees_to_radian(int degrees);
t_vector				vect_rotate_x(t_vector vector, float angle,
		int inverse);
t_vector				vect_rotate_z(t_vector vector, float angle,
		int inverse);
t_vector				vect_rotate_y(t_vector vector, float angle,
		int inverse);
t_object				init_ray(int x, int y, t_camera camera);
float					closest_distance_quadratic(float a, float b, float c);
void					ft_ocl_init_error(const int ret);
void					ft_ocl_kernel_error(const int ret, const size_t index);
size_t					file_len(int fd);
int						hit_test(t_object *clt_obj, t_object *obj,
		t_object l_ray, float norm);
t_object        parse_object(int fd, t_object *object);
t_object		*expand_objects(t_object *objects, int previous_count);
t_vector	point_from_vector(t_point origin, t_vector direction, float norm);
t_scene        create_dependant_objects(t_object object, int fd, t_scene scene);
t_vector		rotate_cylinder_angles(t_object cylinder, t_vector vect,
			int reverse);
t_vector		rotate_cone_angles(t_object cone, t_vector vect,
			int reverse);
t_vector		rotate_vector_angles(t_object reference, t_vector vect,
			int reverse);
t_vector	cross_product(t_vector vect_1, t_vector vect_2);


#endif
