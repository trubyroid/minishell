/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 19:15:19 by truby             #+#    #+#             */
/*   Updated: 2021/07/17 20:50:57 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

static int	ft_check(t_all *command)
{
	int	i;

	i = -1;
	if (strcmp("env", command->command_name) == 0)
	{
		while (command->arg[++i] != NULL)
		{
			if (strcmp("env", command->arg[i]) != 0)
			{
				write(1, "env: ", 5);
				write(1, command->arg[i], ft_strlen(command->arg[i]));
				return (ft_error_int(": No such file or directory"));
			}
		}
	}
	return (1);
}

t_env		*processor(t_all *command, t_env *env, char *home)
{
	pid_t	p;

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
	// else if (strcmp("exit", command->command_name) == 0)
	// 	close_minishell(env, home);												//не декомпозировал
	else if (strcmp("export", command->command_name) == 0)
		ft_export(command, env);												//не декомпозировал
	else
		implementation(command, env);												//не декомпозировал
	return (env);
}