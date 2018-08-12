/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1gpu.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 11:34:03 by aabelque          #+#    #+#             */
/*   Updated: 2018/08/11 18:13:34 by aabelque         ###   ########.fr       */
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

# include <stdio.h>

/*
** ======= macros
*/

# define WIN_HEIGHT 600
# define WIN_WIDTH 900
# define FOV 0.40

# define KEY_ESC 53

# define TRUE 1
# define FALSE 0


/*
** ======= enumerations
*/

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

/*
** ======= structures
*/

typedef struct	s_pixel
{
	int			x;
	int			y;
}				t_pixel;

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

// Cette structure permettra d'identifier :
// - les formes géométriques de la scène
// - les rayons
// Du coup, il faudra bien faire attention à la manière dont on nomme
// les variables de type t_object pour pas se perdre.
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

// Les lignes commentées ci-dessous peuvent être retirées
/*typedef struct	s_sphere
{
	t_point		center;
	float		radius;
	t_color		color;
}				t_sphere;
*/
/*typedef struct	s_plane
{
	t_vector	normal;
	t_point		point;
	t_color		color;
}				t_plane;
*/
/*typedef struct	s_cylinder
{
	t_color		color;
	t_point		point;
	t_vector	direction;
	float		y_angle;
	float		x_angle;
	float		radius;
}				t_cylinder;
*/
/*typedef struct	s_cone
{
	t_color		color;
	t_vector	direction;
	t_point		center;
	float		angle;
	float		y_angle;
	float		x_angle;
}				t_cone;
*/

// On va garder ce type indépendant de t_object.
// Du coup, la liste des lumières passera dans un buffer spécifique quand
// on enverra au GPU.
typedef struct	s_light
{
	t_light_type	typpe;
	t_point			posiition;
	t_vector		direction;
	float			angle;
	t_color			color;
}				t_light;

// Ce type reste, puisqu'il est inclus dans la taille de "env".
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

// Pour la question des pointeurs ici (sachant qu'une structure "t_scene"
// devra être envoyée dans le buffer GPU puisqu'elle dépend de "env") :
// - les pointeurs sont passés en void pour ne pas avoir de problème,
// - avec des cast si necessaire, on retrouve les t_object et t_light
typedef struct	s_scene
{
	void		*objects;
	int			objects_count;
	void		*lights;
	int			lights_count;
}				t_scene;

// A supprimer
/*typedef struct	s_ray
{
	t_vector	direction;
	t_point		origin;
	int			intersect;
	t_point		intersection;
	float		norm;
	t_color		color;
}				t_ray;
*/

// Proposition de structure globale qui regroupera tout ce dont
// on a besoin pour faire tourner l'algo sur GPU.
// Puisque le numéro de pixel est donné par getID, finalement on n'a
// besoin que de "scene" et de "camera", sans pointeur...
typedef struct 	s_data
{
	int 			objects_count; // = env.scene.objects_count
	int 			lights_count; // = env.scene.lights_count
	t_vector 		cam_position; // = env.camera.position
	t_vector		cam_direction; // = env.camera.direction
	t_vector 		plane; // = env.camera.plane
	t_point 		spot; // env.camera.spot
	t_vector 		normal; // = env.camera.normal
	t_vector 		up_left_corner; // = env.camera.up_left_corner
	float 			width; // env.camera.width
	float 			height; // = env.camera.height
	float 			plane_dist; // env.camera.plane_dist
	float 			horizontal_step; // = env.camera.horizontal_step
	float 			vertical_step; // = env.camera.vertical_step
}				t_data;


typedef	struct		s_opencl
{
	size_t				img_s;
	size_t				imgxy[2];
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
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	commands;
	cl_program			program;
	cl_kernel			kernel;
}					t_opencl;

// C'est le dernier type, qui passera dans un troisième
// et dernier buffer spécifique.
// Le seul problème potentiel qu'on a, c'est img_str qui est
// un pointeur sur unsigned char.
// Je me pose la question de créer une structure spécifique pour
// les données à passer au GPU, sans pointeur. (proposition juste
// en dessous)

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
	t_object		object;
	t_camera		camera;
	t_opencl		opcl;
}				t_env;

/*
** ======= prototypes
*/


int				error_gpu(t_opencl *opcl);
void			opencl_init2(t_opencl *opcl, t_env *e);
void			opencl_draw(t_opencl *opcl, t_env *e);
void			set_opencl_env(t_opencl *opcl);
void			create_kernel(cl_program program, cl_kernel *kernel,
		const char *func);
char			*get_kernel_source(char *file);
void			opencl_init(t_opencl *opcl, t_env *env);
void			create_prog(t_opencl *opcl);
void			exit_error(t_env *env);
void			exit_normally(t_env *env);
void			exit_usage(void);
t_env			*init_env(char *file_name);
void			calculate_scene(t_env *env);
t_camera		init_camera(t_env *env);
t_camera		set_camera(int fd, t_env *env);
int				handle_key_event(int key, void *param);
int				expose_event(void *param);
int				exit_properly(void *param);
void			fill_pixel(t_env *env, int x, int y, t_color color);
void			fill_pixel_value(t_env *env, int x, int y, int color_value);
t_vector		vector(float x, float y, float z);
t_vector		vector_points(t_point p1, t_point p2);
t_point			point(float x, float y, float z);
t_pixel			pixel(int x, int y);
t_color			color(int r, int g, int b, int a);
float			vector_norm(t_vector vector);
t_vector		normalize_vector(t_vector vector);
float			dot_product(t_vector vect_1, t_vector vect_2);
float			points_norm(t_point p1, t_point p2);
t_object			intersect_object(t_object ray, t_object object);
t_vector		shape_normal(t_object ray, t_object object);
void			pixel_raytracing(int x, int y, t_env *env);
t_scene			get_sample_scene(void);
t_color			get_color_on_intersection(t_object ray, t_object *closest_object,
	t_env *env);
void			deinit_env(t_env *env);
int				line_len(char **line);
void			clear_line(char **line);
char			**split_new_line(int fd);
t_light			*add_light(int fd, t_light *existing_lights, int count);
t_object		add_new_object(int fd, char *type);
t_scene			create_scene(t_env *env, char *file_name);
t_object			cylinder_intersection(t_object ray, t_object cylinder);
t_object			cone_intersection(t_object ray, t_object cone);
t_object			plane_intersection(t_object ray, t_object plane);
t_object			sphere_intersection(t_object ray, t_object sphere);
t_vector		cone_normal(t_object ray, t_object cone);
t_vector		cylinder_normal(t_object ray, t_object cylinder);
t_vector		plane_normal(t_object ray, t_object plane);
t_vector		sphere_normal(t_object ray, t_object sphere);
float			degrees_to_radian(int degrees);
t_vector		vect_rotate_x(t_vector vector, float angle, int inverse);
t_vector		vect_rotate_z(t_vector vector, float angle, int inverse);
t_vector		vect_rotate_y(t_vector vector, float angle, int inverse);
t_object			init_ray(int x, int y, t_camera camera);
int		debug_mouse_event(int event, int x, int y, void *param);
float			closest_distance_quadratic(float a, float b, float c);

#endif
