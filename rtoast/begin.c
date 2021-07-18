#include "../shell.h"
#include "../truby/shell_truby.h"

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
	int		k;
	int		shlvl;
	t_env	*lst;
	t_env	*new;

	i = 0;
	k = 0;
	while (env[i + 1] != NULL)
		i++;
	lst = malloc(sizeof(t_env *));
	if (!lst)
		return (ft_error_null("Error of malloc."));
	lst->str = env[i];
	lst->next = NULL;
	while (--i >= 0)
	{
		new = malloc(sizeof(t_env *));
		if (!new)
			return (ft_error_null("Error of malloc."));
		new->str = ft_strdup(env[i]);
		if (ft_strnstr(new->str, "SHLVL=", 6))
		{
			while (!ft_isdigit(new->str[k]))
				k++;
			shlvl = 0;
			while (new->str[k] != '\0')
			{
				shlvl = shlvl * 10 + (new->str[k] - '0');
				k++;
			}
			shlvl++;
			free(new->str);
			new->str = NULL;
			new->str = ft_strjoin_shell("SHLVL=", ft_itoa(shlvl));
		}
		new->next = lst;
		lst = new;
	}
	return (lst);
}

void	conrol_d(void)
{
	write(1, "\033[3;1m", 7);
	write(1, ANSI_COLOR_MAGENTA"\e[2Dexit\n"ANSI_COLOR_RESET, 19);
	exit(0);
}
