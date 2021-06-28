#include "shell_truby.h"


char	*ft_strjoin_shell(char *s1, char *s2)																		//надо подключить либу и удалить  эти статик функции
{
	char	*new;
	size_t	i;
	size_t	j;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		new[i] = s1[i];
		i++;
	}
	while (i < ft_strlen(s1) + ft_strlen(s2))
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(s2);
	s2 = NULL;
	return (new);
}

void	change_env(t_env *env)
{
	t_env *lst;
	char *oldpwd;
	char *key;
	char *pwd;

	lst = env;
	pwd = NULL;
	while (ft_strnstr(env->str, "PWD=", 4) == NULL)
	{
		if (env->next == NULL)
			return ;						//error
		env = env->next;
	}
	oldpwd = ft_substr(env->str, 4, ft_strlen(env->str) - 4);
	free(env->str);
	env->str = NULL;
	pwd = getcwd(pwd, 0);
	env->str = ft_strjoin_shell("PWD=", pwd);
	while (ft_strnstr(lst->str, "OLDPWD=", 7) == NULL)
	{
		if (lst->next == NULL)
			return ;						//error
		lst = lst->next;
	}
	free(lst->str);
	lst->str = NULL;
	lst->str = ft_strjoin_shell("OLDPWD=", oldpwd);
}

int use_cd(t_env *env, char **dir, char *home)
{
	char *new_str;

	new_str = NULL;
	if (dir[1] == NULL || dir[1][0] == '~')
	{
		if (dir[1] == NULL || dir[1][1] == '\0')
			chdir(home);
		else
		{
			new_str = ft_substr(dir[1], 1, ft_strlen(dir[1]) - 1);
			new_str = ft_strjoin_shell(home, new_str);										//strjoin фришит старый new_str
			chdir(new_str);
			free(new_str);
			new_str = NULL;
		}
	}
	else if (chdir(dir[1]) == -1)
	{
		printf("cd: %s: %s\n", strerror(errno), dir[0]);
		// g_status = 1;
	}
	change_env(env);
	return (0);
}
