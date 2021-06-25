#include "../shell.h"
#include "../truby/shell_truby.h"

void	close_minishell(t_env *env)
{
	t_env *lst;
	int	i;

	i = -1;
	while (env->next != NULL)
	{
		lst = env;
		env = env->next;
		lst->next = NULL;
		free(lst);
	}
	free(env);
	exit(0);
}

t_env	*creating_list(char **env)
{
	int		i;
	int		j;
	t_env	*lst;
	t_env	*new;
	i = 0;
	j = 0;
	lst = NULL;
	new = NULL;
	while (env[i + 1] != NULL)
		i++;
	j = i;
	lst = malloc(sizeof(t_env *));
	if (!lst)
		return (0);
	lst->str = env[i];
	lst->next = NULL;
	while (--i >= 0)
	{
		new = malloc(sizeof(t_env *));
		if (!new)
			return (0);
		new->str = env[i];
		new->next = lst;
		lst = new;
	}
	return (lst);
}

void	string_creating(t_all *tmp)
{
	write(1, ANSI_COLOR_MAGENTA "💜ya_bash: " ANSI_COLOR_RESET, 23);
	get_next_line(0, &tmp->str);
}

///error
// pwd""
// $* $$...
int	main(int argc, char **argv, char **env)
{
	t_all	*tmp;
	t_env	*lst;
	int		i;

	(void)argc;
	(void)argv;
	tmp = NULL;
	lst = NULL;
	i = 0;
	lst = creating_list(env);
	while (1)
	{
		tmp = (t_all *)malloc(sizeof(t_all));
		tmp->arg = NULL;
		tmp->command_name = NULL;
		string_creating(tmp);
		prepars(tmp, env);
		command_name(tmp);
		lst = processor(tmp, lst);
		free(tmp->str);
		if (tmp->arg != NULL)
		{
			while (tmp->arg[i] != NULL)
			{
				free(tmp->arg[i]);
				i++;
			}
		}
		free(tmp);
	}
	return (0);
}
