#include "../shell.h"
#include "../truby/shell_truby.h"

static void	increase_shlvl(t_env *new)
{
	int	k;
	int	shlvl;

	k = 0;
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
	if (new->str == NULL)
		return (ft_error_exit("Error of malloc.", ENOMEM));
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
	t_env	*lst;
	t_env	*new;

	i = 0;
	while (env[i + 1] != NULL)
		i++;
	lst = malloc(sizeof(t_env *));
	if (!lst)
		return (ft_error_null("Error of malloc.", ENOMEM));
	lst->str = ft_strdup(env[i]);
	lst->next = NULL;
	while (--i >= 0)
	{
		new = malloc(sizeof(t_env *));
		if (!new)
			return (ft_error_null("Error of malloc.", ENOMEM));
		new->str = ft_strdup(env[i]);
		if (ft_strnstr(new->str, "SHLVL=", 6))
			increase_shlvl(new);
		new->next = lst;
		lst = new;
	}
	return (lst);
}

t_env	*copy_lst(t_env *env)
{
	t_env	*new;
	t_env	*extra;
	t_env	*first;

	new = malloc(sizeof(t_env *));
	if (!new)
		return (ft_error_null("Error of malloc.", ENOMEM));
	first = new;
	new->str = env->str;
	env = env->next;
	while (env != NULL)
	{
		extra = malloc(sizeof(t_env *));
		if (!extra)
			return (ft_error_null("Error of malloc.", ENOMEM));
		new->next = extra;
		extra->str = env->str;
		env = env->next;
		if (env != NULL)
			new = extra;
		else
			extra->next = NULL;
	}
	return (first);
}
