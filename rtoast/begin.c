#include "../shell.h"
#include "../truby/shell_truby.h"

void	close_minishell(t_env *env, char *home)
{
	t_env	*lst;

	while (env->str)
	{
		lst = env;
		env = env->next;
		lst->next = NULL;
		// free(lst->str);							//ошибка маллока если экспортировать букву в нижнем регистре
		free(lst);
		lst = NULL;
		if (env->next == NULL)
		{
			// free(env->str);
			free(env);
			break ;
		}
	}
	free(home);
	env = NULL;
	home = NULL;
	exit(0);
}

char	*find_home(void)
{
	char	*pwd;
	char	*home;
	int		i;
	int		fl;

	i = 0;
	fl = 0;
	pwd = NULL;
	home = NULL;
	pwd = getcwd(pwd, 0);
	while (i < ft_strlen(pwd) + 1)
	{
		if (pwd[i] == '/')
			fl++;
		if (fl == 3 || pwd[i] == '\0')
		{
			home = ft_substr(pwd, 0, i);
			break ;
		}
		i++;
	}
	free(pwd);
	pwd = NULL;
	return (home);
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

void	conrol_d(void)
{
	write(1, "\033[3;1m", 7);
	write(1, ANSI_COLOR_MAGENTA"\e[2Dexit\n"ANSI_COLOR_RESET, 19);
	exit (0);
}
