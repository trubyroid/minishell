#include "shell_truby.h"

void		print_env(t_env *env)
{
	int i;

	i = -1;
	while (env->next != NULL)
	{
		if (ft_strchr(env->str, '=') != NULL)
		{
			write(1, env->str, ft_strlen(env->str));
			write(1, "\n", 1);
			env = env->next;
		}
	}
	if (ft_strchr(env->str, '=') != NULL)
	{
		write(1, env->str, ft_strlen(env->str));
		write(1, "\n", 1);
	}
	// exit(0);
}