/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 19:15:12 by truby             #+#    #+#             */
/*   Updated: 2021/07/21 13:37:13 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

static void	writing(t_all *command, int i, int fl)
{
	while (i < command->num_arg - 1)
	{
		write(command->fd_out, command->arg[i], ft_strlen(command->arg[i]));
		write(command->fd_out, " ", 1);
		i++;
	}
	write(command->fd_out, command->arg[i], ft_strlen(command->arg[i]));
	if (fl == 1)
		write(command->fd_out, "\n", 1);
}

void	use_echo(t_all *command)
{
	int	i;

	i = 1;
	if (command->num_arg > 1)
	{
		if (strcmp(command->arg[i], "-n") == 0)
		{
			while (strcmp(command->arg[i], "-n") == 0)
				i++;
			writing(command, i, 0);
		}
		else
			writing(command, i, 1);
	}
	else
		write(command->fd_out, "\n", 1);
	g_status = 0;
}
