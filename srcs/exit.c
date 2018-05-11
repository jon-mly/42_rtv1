#include "rtv1.h"

void		exit_error(t_env *env)
{
	ft_putendl("An error has occured");
	// TODO: handle env deinit
	deinit_env(env);
	exit(0);
}

void		exit_normally(t_env *env)
{
	// TODO: handle env deinit
	deinit_env(env);
	exit(0);
}

void		exit_usage(void)
{
	ft_putendl("Usage : rtv1 [scene descriptor file]");
	exit(0);
}
