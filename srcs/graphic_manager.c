#include "rtv1.h"

void		calculate_scene(t_env *env)
{
	int			x;
	int			y;

	x = -1;
	while (++x < env->win_width)
	{
		y = -1;
		while (++y < env->win_height)
		{
			// TODO:
			// - trace ray 
			// - get color
			// apply color to pixel
			pixel_raytracing(x, y, env);
		}
	}
	ft_putendl("Did end calculate scene");
	mlx_put_image_to_window((void *)env, env->win_ptr, env->img_ptr, 0, 0);
}
