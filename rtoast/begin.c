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
		free(lst->str);
		free(lst);
		lst = NULL;
	}
	free(env);
	free(root);
	env = NULL;
	root = NULL;
	exit(0);
}

static char	*find_home()
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
		new->str = ft_strdup(env[i]);
		new->next = lst;
		lst = new;
	}
	return (lst);
}

void	string_creating(t_all *tmp)
{
		write(1, ANSI_COLOR_MAGENTA"\033[3;1m", 12);
		tmp->str = readline("💜ya_bash: ");
		write(1, ANSI_COLOR_RESET"", 5);
		if (tmp->str && tmp->str[0])
			add_history(tmp->str);
}

///error
// $* $$...
int	main(int argc, char **argv, char **env)
{
	t_all	*tmp;
	t_env	*lst;
	char	*home;
	char	**nenv;
	int		i;

	(void)argc;
	(void)argv;
	tmp = NULL;
	lst = NULL;
	i = 0;
	lst = creating_list(env);
	nenv = rewrite_env(env);
	home = find_home();
	signal(SIGQUIT,  SIG_IGN);
	while (1)
	{
		tmp = (t_all *)malloc(sizeof(t_all));
		string_creating(tmp);
		while (tmp->str)
		{
			tmp->arg = NULL;
			tmp->command_name = NULL;
			prepars(tmp, nenv);
			command_name(tmp);
			lst = processor(tmp, lst, home);
			nenv = list_in_massiv(lst, nenv);
			// free(tmp->str);
			if (tmp->arg != NULL)
			{
				while (i < tmp->num_arg)
				{
					free(tmp->arg[i]);
					tmp->arg[i] = NULL;
					i++;
				}
			}
			free(tmp->str);
			tmp->str = NULL;
			free(tmp);
			tmp = NULL;
			tmp = (t_all *)malloc(sizeof(t_all));
			string_creating(tmp);
		}
		free(nenv);
		conrol_d();
	}
	return (0);
}

int		list_size(t_env	*lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return(i);
}

char	**list_in_massiv(t_env *lst, char **env)
{
	char **new_env;
	int i;
	int l;
	int e;

	i = 0;
	e = -1;
	l = list_size(lst);
	if (env)
	{
		while (env[++e])
			free(env[e]);
		free(env);
	}
	new_env = (char **)malloc(sizeof(char *) * (l + 1));
	new_env[l] = NULL;
	while (i < l)
	{
		new_env[i] = ft_strdup(lst->str);
		i++;
		lst = lst->next;
	}
	return(new_env);
}

char	**rewrite_env(char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = NULL;
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	new_env[i] = NULL;
	i = -1;
	while (env[++i])
		new_env[i] = ft_strdup(env[i]);
	return(new_env);
}

void	conrol_d(void)
{
	write(1, "\033[3;1m", 7);
	write(1, ANSI_COLOR_MAGENTA"\e[2Dexit\n"ANSI_COLOR_RESET, 19);
	exit (0);
}
