#ifndef RTV1_H
# define RTV1_H

/*
** ====== includes
*/

# include "../libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <math.h>

/*
** ======= macros
*/

# define WIN_HEIGHT 400
# define WIN_WIDTH 600
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


/*
** ======= structures
*/

typedef struct	s_point
{
	double		x;
	double		y;
	double		z;
}				t_point;

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
	void			*object;
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
}				t_scene;

typedef struct	s_ray
{
	t_vector	direction;
	t_point		origin;
	int			intersect;
	double		norm;
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
t_env			*init_env(void);
void			calculate_scene(t_env *env);
t_camera		init_camera(t_env *env);
int				handle_key_event(int key, void *param);
void			fill_pixel(t_env *env, int x, int y, t_color color);
void			fill_pixel_value(t_env *env, int x, int y, int color_value);
t_vector		vector(double x, double y, double z);
t_point			point(double x, double y, double z);
t_pixel			pixel(int x, int y);
t_color			color(unsigned char r, unsigned char g, unsigned char b,
	unsigned char a);
double			vector_norm(t_vector vector);
t_vector		normalize_vector(t_vector vector);
double			quadratic_discriminant(double a, double b, double c);
t_ray			sphere_intersection(t_ray ray, t_sphere sphere);
void			pixel_raytracing(int x, int y, t_env *env);
t_scene			get_sample_scene(void);

#endif
