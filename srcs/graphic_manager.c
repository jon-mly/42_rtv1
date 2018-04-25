#include "rtv1.h"

void		calculate_scene(t_env *env)
{
	int			x;
	int			y;

	y = -1;
	while (++y < env->win_height)
	{
		x = -1;
		while (++x < env->win_width)
		{
			pixel_raytracing(x, y, env);
		}
	}
//	printf("IMG width : %d, height : %d, ptr : %p, str : %p", env->img_width, env->img_height, env->img_ptr, env->img_str);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);
	ft_putendl("Did end calculate scene");
}
