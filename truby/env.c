#include "shell_truby.h"

int		print_env(char **env)
{
	int i;

	i = -1;
	while (env[++i] != NULL)
	{
		write(1, env[i], strlen(env[i]));
		write(1, "\n", 1);
	}
	return (0);
}