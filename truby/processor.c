/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 19:15:19 by truby             #+#    #+#             */
/*   Updated: 2021/07/22 13:37:53 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

t_env	*processor(t_all *command, t_env *env, char *home, int fl)
{
	close_dup(command);
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
	else if (ft_strcmp("exit", command->command_name) == 0)
		close_minishell(env, home);
	else if (ft_strcmp("export", command->command_name) == 0)
		ft_export(command, env);
	else
		fork_exec(command, env, fl);
	return (env);
}
