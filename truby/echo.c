#include "shell_truby.h"

int use_echo(t_all *command)
{
	int i = 0;

	if (command->ac > 1)
	{
		while (++i < command->ac - 1)
			printf("%s ", command->arg[i]);
		printf("%s\n", command->arg[i]);
	}
	else
		printf("\n");
}