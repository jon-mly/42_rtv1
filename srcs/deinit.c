#include "rtv1.h"

static void		deinit_scene(t_scene scene)
{
	int			index;

	index = -1;
	while (++index < scene.objects_count)
		ft_memdel(&(scene.objects[index].object));
	ft_memdel((void**)(&(scene.objects)));
	ft_memdel((void**)(&(scene.lights)));
}

void			deinit_env(t_env *env)
{
	deinit_scene(env->scene);
	ft_putendl("Scene is deinited");
	if (env->img_ptr && env->mlx_ptr)
		mlx_destroy_image(env->mlx_ptr, env->img_ptr);
	if (env->win_ptr && env->mlx_ptr)
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	ft_memdel((void**)(&(env->mlx_ptr)));
	ft_memdel((void**)(&env));
}
