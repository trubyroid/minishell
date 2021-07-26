/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 14:45:19 by truby             #+#    #+#             */
/*   Updated: 2021/07/26 12:42:51 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

static void	ft_set_error_code(t_all *command, int g, int o, int i)
{
	if (g >= 0)
	{
		i = 1;
		while (o != g)
		{
			i++;
			o++;
			if (i > 255)
				i = 0;
		}
		exit (i - 1);
	}
	else
	{
		i = 255;
		while (o != g)
		{
			i--;
			o--;
			if (i == -1)
				i = 255;
		}
	}
	exit (i + 1);
}

static void	ft_check_error_code(t_all *command)
{
	int	i;

	i = 0;
	while (command->arg[1][++i] != '\0')
	{
		if (i == 0 && command->arg[1][i] == '-')
			continue ;
		if (!ft_isdigit(command->arg[1][i]))
		{
			write(1, "exit\n", 5);
			write(1, "ya_bash: exit: ", 15);
			write(1, command->arg[1], ft_strlen(command->arg[1]));
			write(1, ": numeric argument required\n", 28);
			exit(255);
		}
	}
}

static void	freeshing(t_env *env, char *home)
{
	t_env	*lst;

	while (env != NULL)
	{
		lst = env;
		env = env->next;
		lst->next = NULL;
		if (lst->str != NULL)
		{
			free(lst->str);
			lst->str = NULL;
			free(lst);
			lst = NULL;
		}
	}
	free(env);
	// free(home);
	env = NULL;
	// home = NULL;
}

void	close_minishell(t_env *env, t_all *command, char *home)
{
	freeshing(env, home);
	if (command->arg[1] != NULL)
	{
		if (ft_isdigit(command->arg[1][0]) || command->arg[1][0] == '-')
		{
			if (command->arg[2] == NULL)
			{
				ft_check_error_code(command);
				ft_set_error_code(command, ft_atoi(command->arg[1]), 0, 0);
			}
			else
			{
				write(1, "exit\n", 5);
				write(1, "ya_bash: exit: too many arguments\n", 34);
				exit(255);
			}
		}
	}
	exit(0);
}
