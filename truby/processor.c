/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 19:15:19 by truby             #+#    #+#             */
/*   Updated: 2021/07/18 18:44:05 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

t_env		*preprocessor(t_all *command, t_env *env, char *home)
{
	int		fd_0;
	int		fd_1;
	// int		fl;
	t_all	*lst;
	// int		*res;

	fd_0 = 0;
	fd_1 = 1;
	dup2(fd_0, 0);
	dup2(fd_1, 1);
	lst = command;
	while (lst != NULL)
	{
		if (lst->baby_pipe != NULL)
		{
			pipe(&lst->fd_pipe[0]);
			dup2(lst->fd_pipe[1], 1);
		}
		env = processor(lst, env, home);
		if (lst->baby_pipe != NULL)
		{
			close(lst->fd_pipe[1]);
			dup2(lst->fd_pipe[0], 0);
		}
		if (lst->baby_pipe == NULL)
		{
			dup2(fd_0, 0);
			dup2(fd_1, 1);
		}
		lst = lst->baby_pipe;
	}
	wait_close(command);
	// g_status = res;
	return (env);
}

t_env		*processor(t_all *command, t_env *env, char *home)
{
	pid_t	p;

	// p = fork();
	// if (p < 0)
	// 	return (ft_error("Fork Failed."));
	// else if (p == 0)
	// {
		if (ft_check(command) == 0)
    		return (env);
		if (strcmp("env", command->command_name) == 0)
			print_env(env);
		else if (strcmp("echo", command->command_name) == 0)						//заменить все strcmp
			use_echo(command);											
		else if (strcmp("pwd", command->command_name) == 0)
			use_pwd(command);
		else if (strcmp("unset", command->command_name) == 0)
			env = delete_enviroment_variable(command, env);
		else if (strcmp("cd", command->command_name) == 0)
			use_cd(env, command->arg, home);
		else if (strcmp("exit", command->command_name) == 0)
			close_minishell(env, home);												//не декомпозировал
		else if (strcmp("export", command->command_name) == 0)
			ft_export(command, env);												//не декомпозировал
		else
			implementation(command, env);												//не декомпозировал
	// }
	// wait(NULL);
	return (env);
}