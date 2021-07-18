#include "../shell.h"
#include "../truby/shell_truby.h"

void	string_creating(t_all *tmp)
{
	write(1, ANSI_COLOR_MAGENTA"\033[3;1m", 12);
	tmp->str = readline("💜ya_bash: ");
	write(1, ANSI_COLOR_RESET"", 5);
	if (tmp->str && tmp->str[0])
		add_history(tmp->str);
}

int	main(int argc, char **argv, char **env)
{
	t_all	*tmp;
	t_env	*lst;

	(void)argc;
	(void)argv;
	tmp = NULL;
	lst = NULL;
	lst = creating_list(env);
	signal(SIGQUIT, SIG_IGN);
	cycle(tmp, lst);
}

void	cycle(t_all *tmp, t_env *lst)
{
	int i;
	int j;
	char *home;

	home = find_home();
	j = 0;
	while (1)
	{
		tmp = (t_all *)malloc(sizeof(t_all));
		string_creating(tmp);
		while (tmp->str)
		{
			i = prepars(tmp);
			if (i == 0)
			{
				command_name(tmp, lst, j);
				printf("%s\n", tmp->command_name);
				printf("%s\n", tmp->arg[0]);
				printf("%s\n", tmp->arg[1]);
				printf("%s\n", tmp->arg[2]);
				if (tmp->command_name)
					lst = processor(tmp, lst, home);
			}
			free_all(tmp);
			tmp = (t_all *)malloc(sizeof(t_all));
			string_creating(tmp);
		}
		conrol_d();
	}
}

void	free_all(t_all *tmp)
{
	int	i;

	i = 0;
	if (tmp->command_name)
		free(tmp->command_name);
	if (tmp->arg != NULL)
	{
		while (i < tmp->num_arg)
		{
			free(tmp->arg[i]);
			tmp->arg[i] = NULL;
			i++;
		}
		free(tmp->arg);
	}
	if (tmp->str)
		free(tmp->str);
	tmp->str = NULL;
	while (tmp->colnum_fd--)
		close(tmp->massiv_fd[tmp->colnum_fd]);
	if (tmp->massiv_fd)
		free(tmp->massiv_fd);
	if (tmp->baby_pipe)
		free_all(tmp->baby_pipe);
	free(tmp);
	tmp = NULL;
}
