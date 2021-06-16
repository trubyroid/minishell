#include "shell_truby.h"

int use_echo(t_all *command)
{
	int i = 0;

	if (command->num_arg > 1)
	{
		while (++i < command->num_arg - 1)
			printf("%s ", command->arg[i]);
		printf("%s", command->arg[i]);
		if (command->arg[1][1] == 'n')
			printf("\n");
	}
	else
		printf("\n");
	return (1);
}