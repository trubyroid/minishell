#include "shell.h"
#include "../libft/get_next_line.h"

void	string_creating(t_all *tmp)
{
	write(1, "write command ", 14);
	get_next_line(0, &tmp->str);
}

// проверить доллар
// "'" && '"'
int	main(int argc, char **argv, char **env)
{
	t_all	*tmp;

	tmp = (t_all *)malloc(sizeof(tmp));
	tmp->arg = NULL;
	tmp->command_name = NULL;
	string_creating(tmp);
	prepars(tmp);
	command_name(tmp);
	printf("name = %s\n", tmp->command_name);
	// printf("argument = %s\n", tmp->arg[0]);
	// printf("argument = %s\n", tmp->arg[1]);
	free(tmp->str);
	free(tmp->command_name);
	// free(tmp->arg[0]);
	// free(tmp->arg[1]);
	// free(tmp->arg);
	free(tmp);
}
