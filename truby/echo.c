#include "shell_truby.h"

int use_echo(t_all *command)
{
	int i = 0;

	if (command->num_arg > 1)
	{
		while (++i < command->num_arg - 1)
			printf("%s ", command->arg[i]);
		printf("%s\n", command->arg[i]);
	}
	else
		printf("\n");
}