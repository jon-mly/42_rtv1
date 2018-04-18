#include "rtv1.h"

int			handle_key_event(int key, void *param)
{
	t_env		*env;

	env = (t_env*)param;
	if (key == KEY_ESC)
		exit_normally(env);
	return (0);
}
