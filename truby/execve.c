/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 17:09:51 by truby             #+#    #+#             */
/*   Updated: 2021/07/18 20:21:09 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

static char	**create_massiv(t_env *env)
{
	t_env	*first;
	int		i;
	char	**env_massiv;

	i = 0;
	first = env;
	while (env->str)
	{
		i++;
		if (env->next == NULL)
			break ;
		env = env->next;
	}
	env_massiv = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (first->str)
	{
		env_massiv[++i] = ft_strdup(first->str);
		if (first->next == NULL)
			break ;
		first = first->next;
	}
	env_massiv[++i] = NULL;
	return (env_massiv);
}

void	exec(t_all *command, t_env *env)
{
	int i = -1;
	int j = -1;
	int res = -1;
	int k;
	int fl = 0;
	char *str = NULL;
	char *path = NULL;
	char **paths = NULL;
	char **env_massiv;

	env_massiv = create_massiv(env);
	while (ft_strnstr(env->str, "PATH=", 5) == NULL)
	{
		if (env->next == NULL)
		{
			write(1, "ya_bash: ", 9);
			write(1, command->arg[0], ft_strlen(command->arg[0]));
			return (ft_error(": No such file or directory"));
		}
		env = env->next;
	}
	str = ft_substr(env->str, 5, ft_strlen(env->str) - 5);
	paths = ft_split(str, ':');
	free(str);
	str = NULL;
	if (strcmp("./", command->command_name) == 0)							//заменить strcmp
	{
		str = ft_strjoin("/", command->arg[0]);
		path = ft_strjoin_gnl(getcwd(NULL, 0), str);
		res = execve(path, command->arg, env_massiv);
		free(path);
		path = NULL;
	}
	else if (strcmp("../", command->command_name) == 0)
	{
		path = getcwd(NULL, 0);
		k = ft_strlen_int(path);
		while (--k != 0)
		{
			if (path[k] == '/')
				break ;
		}
		path = ft_strjoin_gnl(ft_substr_shell(path, 0, k), command->arg[0]);
		res = execve(path, command->arg, env_massiv);
		free(path);
		path = NULL;
	}
	else if (ft_strchr(command->command_name, '/'))
		res = execve(command->command_name, &command->arg[0], env_massiv);
	else
	{
		while(res == -1 && paths[++i] != NULL)
		{
			str = ft_strjoin("/", command->command_name);
			path = ft_strjoin(paths[i], str);
			free(str);
			str = NULL;
			res = execve(path, command->arg, env_massiv);
			free(path);
			path = NULL;
			if (res != -1)
				break ;
		}
	}
	while(paths[++j] != NULL)
	{
		free(paths[j]);
		paths[j] = NULL;
	}
	j = -1;
	// while(env_massiv[++j] != NULL)														//ошибка маллока
	// {
	// 	free(env_massiv[j]);
	// 	env_massiv[j] = NULL;
	// }
	free(paths);
	free(env_massiv);
	exit(errno);
}

void	implementation(t_all *command, t_env *env)
{
	pid_t p;
	int	  res;
	
	p = fork();
	if (p < 0)
		return (ft_error("Fork Failed."));
	else if (p == 0)
	{
		if (command->fd_out != 1)
		{
			close(1);
			dup2(command->fd_out, 1);
		}
		if (command->fd_in != 0)
		{
			close(0);
			dup2(command->fd_in, 0);
		}
		exec(command, env);
	}
	wait(&res);
	// g_status = res / 256;
}