#include "shell_truby.h"

int use_echo(t_all *command)
{
	int i;

	i = 1;
	if (command->num_arg > 1)
	{
		if (strcmp(command->arg[i], "-n") == 0)
		{
			while (strcmp(command->arg[i], "-n") == 0)
				i++;
			while (i < command->num_arg - 1)
			{
				write(1, command->arg[i], ft_strlen(command->arg[i]));
				write(1, " ", 1);
				i++;
			}
			write(1, command->arg[i], ft_strlen(command->arg[i]));
		}
		else
		{
			while (i < command->num_arg - 1)
			{
				write(1, command->arg[i], ft_strlen(command->arg[i]));
				write(1, " ", 1);
				i++;
			}
			write(1, command->arg[i], ft_strlen(command->arg[i]));
			write(1, "\n", 1);
		}
	}
	else
		write(1, "\n", 1);
	return (1);
}