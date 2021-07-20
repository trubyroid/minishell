/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 05:54:24 by truby             #+#    #+#             */
/*   Updated: 2021/07/20 05:54:29 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

void	use_pwd(t_all *command)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(NULL, 0);
	write(command->fd_out, dir, ft_strlen(dir));
	write(command->fd_out, "\n", 1);
	free(dir);
	dir = NULL;
}
