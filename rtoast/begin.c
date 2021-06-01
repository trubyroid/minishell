#include "shell.h"
#include "../libft/get_next_line.h"

void string_creating(t_all *tmp)
{
	write(1, "write command ", 14);
	get_next_line(0, &tmp->str);
}

int main(int argc, char **argv, char **env)
{
	t_all *tmp;

	tmp = (t_all *)malloc(sizeof(tmp));
	tmp->arg = NULL;
	string_creating(tmp);
	prepars(tmp);
	start(tmp);
	printf("name = %s\n", tmp->command_name);
	printf("argument = %s\n", tmp->arg[0]);
	printf("argument = %s\n", tmp->arg[1]);
	free(tmp->arg);
	free(tmp->str);
	free(tmp->command_name);
	free(tmp);
}
