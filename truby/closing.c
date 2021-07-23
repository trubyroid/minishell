/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 14:45:19 by truby             #+#    #+#             */
/*   Updated: 2021/07/23 03:35:06 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

void	ft_error(char *str, int i)
{
	g_status = i;
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

void	ft_error_exit(char *str, int i)
{
	g_status = i;
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit(i);
}

int	ft_error_int(char *str, int i, int fl)
{
	g_status = i;
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	if (fl == 1)
		exit(i);
	return (0);
}

void	*ft_error_null(char *str, int i)
{
	g_status = i;
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (NULL);
}

void	close_minishell(t_env *env, t_all *command, char *home)
{
	t_env	*lst;
	int		i;

	i = -1;
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
	free(home);
	env = NULL;
	home = NULL;
	if (ft_isdigit(command->arg[1][++i])
	{
		while (ft_command->arg[1][++i] != '\0')
		{
			if (!ft_isdigit(command->arg[1][i])
				exit(0);
		}
		g_status = ft_atoi(command->arg[1]);								//добавить обновление счетчика
		exit(g_status);
	}
	exit(0);
}
