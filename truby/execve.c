/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 17:09:51 by truby             #+#    #+#             */
/*   Updated: 2021/07/12 19:10:31 by truby            ###   ########.fr       */
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
	return (env_massiv);
}

void	exec(t_all *command, t_env *env)
{
	int i = -1;
	int j = -1;
	int res = -1;
	char *str = NULL;
	char *path = NULL;
	char **paths = NULL;
	char **env_massiv;

	env_massiv = create_massiv(env);
	while (ft_strnstr(env->str, "PATH=", 5) == NULL)
	{
		if (env->next == NULL)
			return ;						//error
		env = env->next;
	}
	str = ft_substr(env->str, 5, ft_strlen(env->str) - 5);
	paths = ft_split(str, ':');
	free(str);
	str = NULL;
	if (strcmp("./", command->command_name) == 0)							//заменить strcmp
	{
		path = ft_strjoin(getcwd(NULL, 0), command->arg[0]);
		res = execve(path, &command->arg[0], env_massiv);
		free(path);
		path = NULL;
	}
	else
	{
		while(res == -1 && paths[++i] != NULL)
		{
			str = ft_strjoin("/", command->command_name);
			path = ft_strjoin(paths[i], str);
			free(str);
			str = NULL;														//придумать как зафришить path, paths и env_massiv в случае успеха execve
			res = execve(path, &command->arg[0], env_massiv);
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
}


void	implementation(t_all *command, t_env *env)
{
	pid_t p;
	
	p = fork();
	if (p < 0)
    {
        write(1, "Fork Failed.", 12);
        return ;							//error
    }
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
		exec(command, env);									//shlvl zsh minishell bash
	}
	wait(NULL);
}