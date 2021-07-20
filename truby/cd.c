/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 21:12:00 by truby             #+#    #+#             */
/*   Updated: 2021/07/20 05:52:04 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

static t_env	*find_variable(t_env *env, char *str, int q)
{
	while (ft_strnstr(env->str, str, q) == NULL)
	{
		if (env->next == NULL)
			return (NULL);
		env = env->next;
	}
	return (env);
}

static void	change_env(t_env *env)
{
	t_env	*lst;
	char	*oldpwd;
	char	*key;
	char	*pwd;

	lst = env;
	pwd = NULL;
	env = find_variable(env, "PWD=", 4);
	if (env == NULL)
		return ;
	oldpwd = ft_substr(env->str, 4, ft_strlen(env->str) - 4);
	free(env->str);
	env->str = NULL;
	pwd = getcwd(pwd, 0);
	env->str = ft_strjoin_shell("PWD=", pwd);
	if (env->str == NULL || oldpwd == NULL)
		return (ft_error("Error of malloc.", ENOMEM));
	lst = find_variable(lst, "OLDPWD=", 7);
	if (lst == NULL)
		return ;
	free(lst->str);
	lst->str = NULL;
	lst->str = ft_strjoin_shell("OLDPWD=", oldpwd);
	if (lst->str == NULL)
		return (ft_error("Error of malloc.", ENOMEM));
}

void	use_cd(t_env *env, char **dir, char *home)
{
	char	*new_str;

	if (dir[1] == NULL || dir[1][0] == '~')
	{
		if (dir[1] == NULL || dir[1][1] == '\0')
			chdir(home);
		else
		{
			new_str = ft_substr(dir[1], 1, ft_strlen(dir[1]) - 1);
			if (new_str == NULL)
				return (ft_error("Error of malloc.", ENOMEM));
			new_str = ft_strjoin_shell(home, new_str);
			if (new_str == NULL)
				return (ft_error("Error of malloc.", ENOMEM));
			if (chdir(new_str) == -1)
			{
				write(1, "ya_bash: cd: ", 13);
				write(1, new_str, ft_strlen(new_str));
				free(new_str);
				new_str = NULL;
				return (ft_error(": No such file or directory", 1));
			}
			free(new_str);
			new_str = NULL;
		}
	}
	else if (chdir(dir[1]) == -1)
	{
		write(1, "ya_bash: cd: ", 13);
		write(1, dir[1], ft_strlen(dir[1]));
		return (ft_error(": No such file or directory", 1));
	}
	change_env(env);
}
