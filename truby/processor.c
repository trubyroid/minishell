/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 19:15:19 by truby             #+#    #+#             */
/*   Updated: 2021/07/20 04:07:57 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

t_env		*preprocessor(t_all *command, t_env *env, char *home)
{
	t_all	*lst;
	pid_t	*pid;
	int		fd_0;
	int 	len;
	int		i;
	int 	**fd;

	if (command->baby_pipe == NULL)
		env = processor(command, env, home, 0);
	else
	{
		i = -1;
		len = babylist_len(command);
		fd_0 = dup(0);
		fd = malloc(sizeof(int *) * len);
		if (!fd)
			return (ft_error_null("Error of malloc.", ENOMEM));
		fd[len - 1] = NULL;
		pid = malloc(sizeof(pid_t) * len);
		if (!pid)
			return (ft_error_null("Error of malloc.", ENOMEM));
		while (++i < len)
		{
			fd[i] = malloc(sizeof(int) * 2);
			if (!fd[i])
				return (ft_error_null("Error of malloc.", ENOMEM));
		}
		i = -1;
		while (++i < len)
		{
			if (pipe(fd[i]) == -1)
				return (ft_error_null("Pipe failed.", errno));
		}
		lst = command;
		i = -1;
		while (lst != NULL && ++i < len + 1)
		{
			pid[i] = fork();
			// if (pid[i] < 0)
			// 	return (ft_error_null("Fork failed.", errno));							//спросить
			if (pid[i] != 0)
				close(fd[i][1]);
			else if (!pid[i])
			{
				if (i == 0)
				{
					close(fd[i][0]);
					dup2(fd[i][1], 1);
				}
				else if (i < len - 1)
				{
					close(fd[i - 1][1]);
					dup2(fd[i - 1][0], 0);
					close(fd[i][0]);
					dup2(fd[i][1], 1);
				}
				else 
				{
					close(fd[i - 1][1]);
					dup2(fd[i - 1][0], 0);
				}
				env = processor(lst, env, home, 1);
			}
			lst = lst->baby_pipe;
		}
		i = -1;
		while (++i < len + 1)
			wait(&pid[i]);
		dup2(fd_0, 0);
		// wait_close(command);
	}
	return (env);
}

t_env		*processor(t_all *command, t_env *env, char *home, int fl)
{
	if (ft_check(command) == 0)
    	return (env);
	if (ft_strcmp("env", command->command_name) == 0)
		print_env(env);
	else if (ft_strcmp("echo", command->command_name) == 0)
		use_echo(command);											
	else if (ft_strcmp("pwd", command->command_name) == 0)
		use_pwd(command);
	else if (ft_strcmp("unset", command->command_name) == 0)
		env = delete_enviroment_variable(command, env);
	else if (ft_strcmp("cd", command->command_name) == 0)
		use_cd(env, command->arg, home);
	// else if (ft_strcmp("exit", command->command_name) == 0)
	// 	close_minishell(env, home);												//не декомпозировал
	else if (ft_strcmp("export", command->command_name) == 0)
		ft_export(command, env);												//не декомпозировал
	else
		implementation(command, env, fl);												//не декомпозировал
	return (env);
}