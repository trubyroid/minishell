/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 14:45:19 by truby             #+#    #+#             */
/*   Updated: 2021/07/19 18:54:15 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

void	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

int		ft_error_int(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (0);
}

void	*ft_error_null(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (NULL);
}

void	wait_close(t_all *command)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (i < babylist_len(command))
	{
		wait(&res);
		// g_status=
		res = 0;
		i++;
	}
	while (command != NULL)
	{
		if (command->baby_pipe != NULL)
		{
			if (command->fd_pipe[0] > 0)
				close(command->fd_pipe[0]);
		}
		// if (command->fd_in > 0)
		// 	close(command->fd_in);
		command = command->baby_pipe;
	}
}

void	close_minishell(t_env *env, char *home)
{
	t_env	*lst;

	while (env->next != NULL)
	{
		lst = env;
		env = env->next;
		lst->next = NULL;
		// free(lst->str);							//ошибка маллока 
		free(lst);
		lst = NULL;
	}
	free(env);
	free(home);
	env = NULL;
	home = NULL;
	exit(errno);
}