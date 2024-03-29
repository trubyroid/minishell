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
	cycle(tmp, lst);
}

void	cycle(t_all *tmp, t_env *lst)
{
	int		j;
	char	*home;

	j = 0;
	signal_normal();
	tmp = (t_all *)malloc(sizeof(t_all));
	home = find_home();
	string_creating(tmp);
	while (tmp->str)
	{
		signal_cat();
		if (prepars(tmp) == 0)
		{
			command_name(tmp, lst, j);
			if (tmp->command_name)
				lst = preprocessor(tmp, lst, home);
		}
		free_all(tmp);
		tmp = (t_all *)malloc(sizeof(t_all));
		signal_normal();
		string_creating(tmp);
	}
	free(home);
	conrol_d();
}

void	free_all(t_all *tmp)
{
	int	i;

	i = -1;
	if (tmp->command_name)
		free(tmp->command_name);
	if (tmp->arg != NULL)
	{
		while (++i < tmp->num_arg)
		{
			free(tmp->arg[i]);
			tmp->arg[i] = NULL;
		}
		free(tmp->arg);
	}
	free_two(tmp);
}

void	free_two(t_all *tmp)
{
	if (tmp->str)
		free(tmp->str);
	tmp->str = NULL;
	while (tmp->colnum_fd--)
		close(tmp->massiv_fd[tmp->colnum_fd]);
	if (tmp->massiv_fd)
		free(tmp->massiv_fd);
	if (tmp->baby_pipe)
		free_all(tmp->baby_pipe);
	if (tmp->file_name)
		free(tmp->file_name);
	free(tmp);
	tmp = NULL;
}
