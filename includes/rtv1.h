/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 12:31:54 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/07/23 13:40:07 by jmlynarc         ###   ########.fr       */
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

# include <stdio.h>

/*
** ======= macros
*/

# define WIN_HEIGHT 800
# define WIN_WIDTH 1200
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
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef t_vector	t_point;

typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}				t_color;

typedef struct	s_object
{
	t_object_type	type;
	t_color			color;
	double			y_angle;
	double			x_angle;
	void			*object;
	char			*name;
}				t_object;

typedef struct	s_sphere
{
	t_point		center;
	double		radius;
	t_color		color;
}				t_sphere;

typedef struct	s_plane
{
	t_vector	normal;
	t_point		point;
	t_color		color;
}				t_plane;

typedef struct	s_cylinder
{
	t_color		color;
	t_point		point;
	t_vector	direction;
	double		y_angle;
	double		x_angle;
	double		radius;
}				t_cylinder;

typedef struct	s_cone
{
	t_color		color;
	t_vector	direction;
	t_point		center;
	double		angle;
	double		y_angle;
	double		x_angle;
}				t_cone;

typedef struct	s_light
{
	t_light_type	type;
	t_point			position;
	t_vector		direction;
	double			angle;
	t_color			color;
}				t_light;

typedef struct	s_camera
{
	t_vector	position;
	t_vector	direction;
	t_vector	plane;
	t_point		spot;
	t_vector	normal;
	t_vector	up_left_corner;
	double		width;
	double		height;
	double		plane_dist;
	double		horizontal_step;
	double		vertical_step;
}				t_camera;

typedef struct	s_scene
{
	t_object	*objects;
	int			objects_count;
	t_light		*lights;
	int			lights_count;
}				t_scene;

typedef struct	s_ray
{
	t_vector	direction;
	t_point		origin;
	int			intersect;
	t_point		intersection;
	double		norm;
	t_color		color;
}				t_ray;

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
}				t_env;

/*
** ======= prototypes
*/

void			exit_error(t_env *env);
void			exit_normally(t_env *env);
void			exit_usage(void);
t_env			*init_env(char *file_name);
void			calculate_scene(t_env *env);
t_camera		init_camera(t_env *env);
int				handle_key_event(int key, void *param);
int				expose_event(void *param);
void			fill_pixel(t_env *env, int x, int y, t_color color);
void			fill_pixel_value(t_env *env, int x, int y, int color_value);
t_vector		vector(double x, double y, double z);
t_vector		vector_points(t_point p1, t_point p2);
t_point			point(double x, double y, double z);
t_pixel			pixel(int x, int y);
t_color			color(int r, int g, int b, int a);
double			vector_norm(t_vector vector);
t_vector		normalize_vector(t_vector vector);
double			dot_product(t_vector vect_1, t_vector vect_2);
double			points_norm(t_point p1, t_point p2);
t_ray			intersect_object(t_ray ray, t_object object);
t_vector		shape_normal(t_ray ray, t_object object);
void			pixel_raytracing(int x, int y, t_env *env);
t_scene			get_sample_scene(void);
t_color			get_color_on_intersection(t_ray ray, t_object *closest_object,
	t_env *env);
void			deinit_env(t_env *env);
int				line_len(char **line);
void			clear_line(char **line);
char			**split_new_line(int fd);
t_light			*add_light(int fd, t_light *existing_lights, int count);
t_object		add_new_object(int fd, char *type);
t_scene			create_scene(t_env *env, char *file_name);
t_ray			cylinder_intersection(t_ray ray, t_cylinder cylinder);
t_ray			cone_intersection(t_ray ray, t_cone cone);
double			degrees_to_radian(int degrees);
t_vector		vect_rotate_x(t_vector vector, double angle);
t_vector		vect_rotate_z(t_vector vector, double angle);
t_vector		vect_rotate_y(t_vector vector, double angle);

#endif
