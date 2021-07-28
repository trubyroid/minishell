/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 17:09:51 by truby             #+#    #+#             */
/*   Updated: 2021/07/28 15:17:07 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

static void	try_that_direction(t_all *command, char *dir, char **env_massiv)
{
	char	*path;
	char	*str;

	str = ft_strjoin("/", command->arg[0]);
	if (!str)
		return (ft_error_exit("Error of malloc.", ENOMEM));
	path = ft_strjoin(dir, str);
	if (!path)
		return (ft_error_exit("Error of malloc.", ENOMEM));
	free(str);
	str = NULL;
	execve(path, command->arg, env_massiv);
	free(path);
	path = NULL;
	free(dir);
	dir = NULL;
}

static void	previous_direction(t_all *command, char *dir, char **env_massiv)
{
	int		k;
	char	*str;

	k = ft_strlen_int(dir);
	while (--k != 0)
	{
		if (dir[k] == '/')
			break ;
	}
	str = ft_substr(dir, 0, k + 1);
	free(dir);
	dir = ft_strjoin_gnl(str, command->arg[0]);
	if (!dir)
		return (ft_error_exit("Error of malloc.", ENOMEM));
	execve(dir, command->arg, env_massiv);
	free(dir);
	dir = NULL;
}

static void	find_prog(t_all *command, char **paths, char **env, char *pwd)
{
	int	i;

	i = -1;
	while (paths[++i] != NULL)
		try_that_direction(command, paths[i], env);
	if (command->fd_in == 0 && command->fd_out == 1)
	{
		free_massives(paths, env, pwd, 0);
		write(1, "ya_bash: ", 9);
		write(1, command->arg[0], ft_strlen(command->arg[0]));
		return (ft_error_exit(": command not found", 127));
	}
}

static void	exec_processor(t_all *command, char *pwd, char **env, char **paths)
{
	if (ft_strcmp("./", command->command_name) == 0
		&& command->arg[0] != NULL)
		try_that_direction(command, pwd, env);
	else if (ft_strcmp("../", command->command_name) == 0
		&& command->arg[0] != NULL)
		previous_direction(command, pwd, env);
	else if (ft_strchr(command->command_name, '/'))
		execve(command->command_name, command->arg, env);
	else
		find_prog(command, paths, env, pwd);
}

void	implementation(t_all *command, t_env *env)
{
	char	*pwd;
	char	*str;
	char	**paths;
	char	**env_massiv;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	env_massiv = create_massiv(env);
	if (!env_massiv)
		return ;
	env = find_variable(env, "PATH=", command->arg[0], 2);
	str = ft_substr(env->str, 5, ft_strlen(env->str) - 5);
	if (!str)
		return (ft_error_exit("Error of malloc.", ENOMEM));
	paths = ft_split(str, ':');
	if (!paths)
		return (ft_error_exit("Error of malloc.", ENOMEM));
	free(str);
	str = NULL;
	exec_processor(command, pwd, env_massiv, paths);
	free_massives(paths, env_massiv, pwd, 1);
	write(1, "ya_bass: ", 9);
	write(1, command->arg[0], ft_strlen(command->arg[0]));
	return (ft_error_exit(": No such file", 127));
}
