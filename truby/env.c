#include "shell_truby.h"

int		print_env(t_env *env)
{
	int i;

	i = -1;
	while (env->next != NULL)
	{
		write(1, env->str, strlen(env->str));
		write(1, "\n", 1);
		env = env->next;
	}
	write(1, env->str, strlen(env->str));
	write(1, "\n", 1);
	return (0);
}