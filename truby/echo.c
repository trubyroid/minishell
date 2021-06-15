#include "shell_truby.h"

int use_echo(t_all *command)
{
	int i =-1;

	if (command->num_arg > 0)
	{
		while (++i < command->num_arg - 1)
			printf("%s ", command->arg[i]);
		printf("%s\n", command->arg[i]);
	}
	else
		printf("\n");
	return (1);
}