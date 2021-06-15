#include "../shell.h"
#include "../truby/shell_truby.h"
#include "../libft/get_next_line.h"

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
	write(1, "ya_bash: ", 9);
	get_next_line(0, &tmp->str);
}

// проверить доллар
// "'" && '"'
int	main(int argc, char **argv, char **env)
{
	t_all	*tmp;
	t_env	*lst;
	int		i;

	(void)argc;
	(void)argv;
	tmp = NULL;
	lst = NULL;
	i = -1;
	lst = creating_list(env);
	while (1)
	{
		tmp = (t_all *)malloc(sizeof(t_all));
		tmp->arg = NULL;
		tmp->command_name = NULL;
		string_creating(tmp);
		prepars(tmp);
		command_name(tmp);
		processor(tmp, lst);
		// printf("name = %s\n", tmp->command_name);
		// printf("argument = %s\n", tmp->arg[0]);
		// printf("argument = %s\n", tmp->arg[1]);
		// printf("arg_num = %d\n", tmp->num_arg);
		free(tmp->str);
		free(tmp->command_name);
		if (tmp->arg != NULL)
		{
			while (tmp->arg[++i] != NULL)
				free(tmp->arg[i]);
			free(tmp->arg);
		}
		free(tmp);
	}
	return (0);
}
