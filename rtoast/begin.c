#include "../shell.h"
#include "../truby/shell_truby.h"

void	close_minishell(t_env *env, char *root)
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
		lst = NULL;
	}
	free(env);
	free(root);
	env = NULL;
	root = NULL;
	exit(0);
}

static char	*find_root()
{
	char *pwd;
	char *root;
	int		i;
	int		fl;

	i = 0;
	fl = 0;
	pwd = NULL;
	root = NULL;
	pwd = getcwd(pwd, 0);
	while (i < ft_strlen(pwd) + 1)
	{
		if (pwd[i] == '/')
			fl++;
		if (fl == 3 || pwd[i] == '\0')
		{
			root = ft_substr(pwd, 0, i);
			break ;
		}
		i++;
	}
	free(pwd);
	pwd = NULL;
	return (root);
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
	char	*root;
	int		i;

	(void)argc;
	(void)argv;
	tmp = NULL;
	lst = NULL;
	i = 0;
	lst = creating_list(env);
	root = find_root();
	while (1)
	{
		tmp = (t_all *)malloc(sizeof(t_all));
		tmp->arg = NULL;
		tmp->command_name = NULL;
		string_creating(tmp);
		prepars(tmp, env);
		command_name(tmp);
		lst = processor(tmp, lst, root);
		free(tmp->str);
		tmp->str = NULL;
		if (tmp->arg != NULL)
		{
			while (tmp->arg[i] != NULL)
			{
				free(tmp->arg[i]);
				tmp->arg[i] = NULL;
				i++;
			}
		}
		free(tmp);
		tmp = NULL;
	}
	return (0);
}
