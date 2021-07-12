#include "shell_truby.h"

void use_pwd(t_all *command)
{
	char *dir = NULL;

	dir = getcwd(NULL, 0);
	write(command->fd_out, dir, ft_strlen(dir));
	write(command->fd_out, "\n", 1);
	free(dir);
	dir = NULL;
}