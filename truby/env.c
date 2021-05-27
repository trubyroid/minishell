#include <stdio.h>
#include <string.h>
#include <unistd.h>

int		main(int ac, char **av, char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		write(1, env[i], strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}