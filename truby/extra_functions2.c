/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 15:34:14 by truby             #+#    #+#             */
/*   Updated: 2021/07/22 18:44:26 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

void	close_dup(t_all *command)
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
}

void	fork_exec(t_all *command, t_env *env, int fl)
{
	pid_t	p;
	int		res;
	int		fd_0;
	int		fd_1;

	fd_0 = dup(0);
	fd_1 = dup(1);
	if (fl == 0)
	{
		p = fork();
		if (p < 0)
			return (ft_error("Fork failed.", errno));
		else if (p == 0)
			implementation(command, env);
		wait(&res);
		dup2(fd_0, 0);
		dup2(fd_1, 1);
		g_status = res / 256;
	}
	else
		implementation(command, env);
}

int	validation(char *arg_str)
{
	int	i;
	int	k;

	i = 1;
	if (!ft_isalpha(arg_str[0]) && arg_str[k] != '_')
		return (-1);
	while (arg_str[i] != '=' && arg_str[i])
	{
		if (!ft_isalnum(arg_str[i]))
			return (-1);
		i++;
	}
	k = i;
	while (arg_str[++k] != '\0')
	{
		if (arg_str[k] < 42
			&& arg_str[k] > 57 && arg_str[k] < 63)
			return (-1);
	}
	if (arg_str[i] == '=')
		return (i + 1);
	return (0);
}

char	**create_massiv(t_env *env)
{
	t_env	*first;
	int		i;
	char	**env_massiv;

	i = 0;
	first = env;
	while (env != NULL)
	{
		i++;
		env = env->next;
	}
	env_massiv = malloc(sizeof(char *) * (i + 1));
	if (!env_massiv)
		return (ft_error_null("Error of malloc.", ENOMEM));
	i = -1;
	while (first != NULL)
	{
		env_massiv[++i] = ft_strdup(first->str);
		if (!env_massiv[i])
			return (ft_error_null("Error of malloc.", ENOMEM));
		first = first->next;
	}
	env_massiv[i + 1] = NULL;
	return (env_massiv);
}

void	free_massives(char **paths, char **env_massiv, char *pwd, int fl)
{
	int	i;

	i = -1;
	while (env_massiv[++i] != NULL)
	{
		free(env_massiv[i]);
		env_massiv[i] = NULL;
	}
	i = -1;
	if (fl == 1)
	{
		while (paths[++i] != NULL)
		{
			free(paths[i]);
			paths[i] = NULL;
		}
	}
	free(paths);
	free(env_massiv);
	free(pwd);
}
