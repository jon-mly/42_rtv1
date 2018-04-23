#include "rtv1.h"

int		main(int ac, char **av)
{
	t_env		*env;

	env = init_env();
	calculate_scene(env);
	mlx_key_hook(env->win_ptr, handle_key_event, (void*)env);
	mlx_loop(env->mlx_ptr);
	return (0);
}
