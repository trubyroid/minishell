/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 21:12:00 by truby             #+#    #+#             */
/*   Updated: 2021/07/20 22:00:17 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

static void	change_env(t_env *env)
{
	t_env	*lst;
	char	*oldpwd;
	char	*key;
	char	*pwd;

	lst = env;
	pwd = NULL;
	env = find_variable(env, "PWD=", 0);
	if (env == NULL)
		return ;
	oldpwd = ft_substr(env->str, 4, ft_strlen(env->str) - 4);
	free(env->str);
	env->str = NULL;
	pwd = getcwd(pwd, 0);
	env->str = ft_strjoin_shell("PWD=", pwd);
	if (env->str == NULL || oldpwd == NULL)
		return (ft_error("Error of malloc.", ENOMEM));
	lst = find_variable(lst, "OLDPWD=", 0);
	if (lst == NULL)
		return ;
	free(lst->str);
	lst->str = NULL;
	lst->str = ft_strjoin_shell("OLDPWD=", oldpwd);
	if (lst->str == NULL)
		return (ft_error("Error of malloc.", ENOMEM));
}

static void	chdir_with_tilda(char *home, char *dir)
{
	char	*new_str;

	new_str = ft_substr(dir, 1, ft_strlen(dir) - 1);
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

static void	back_to_previous(t_env *env)
{
	int		i;
	char	*oldpwd;

	i = 0;
	env = find_variable(env, "OLDPWD=", 1);
	if (env == NULL)
		return ;
	while (env->str[i] != '=')
		i++;
	i++;
	oldpwd = ft_substr(env->str, i, ft_strlen(env->str) - i);
	if (oldpwd == NULL)
		return (ft_error("Error of malloc.", ENOMEM));
	write(1, oldpwd, ft_strlen(oldpwd));
	write(1, "\n", 1);
	chdir(oldpwd);
	free(oldpwd);
	oldpwd = NULL;
}

void	use_cd(t_env *env, char **dir, char *home)
{
	char	*new_str;

	if (dir[1] == NULL || dir[1][0] == '~')
	{
		if (dir[1] == NULL || dir[1][1] == '\0')
			chdir(home);
		else
			chdir_with_tilda(home, dir[1]);
	}
	else if (ft_strcmp(dir[1], "-") == 0)
		back_to_previous(env);
	else if (chdir(dir[1]) == -1)
	{
		write(1, "ya_bash: cd: ", 13);
		write(1, dir[1], ft_strlen(dir[1]));
		return (ft_error(": No such file or directory", 1));
	}
	change_env(env);
}
