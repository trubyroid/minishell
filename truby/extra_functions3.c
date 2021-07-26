/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 12:28:05 by truby             #+#    #+#             */
/*   Updated: 2021/07/26 12:31:12 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

void	ft_check_malloc(void *obj)
{
	if (obj == NULL)
		return (ft_error_exit("Error of malloc.", ENOMEM));
}

void	post_work(int len, pid_t *pid, int **fd)
{
	int	i;

	i = -1;
	while (++i < len + 1)
		wait(&pid[i]);
	i = -1;
	while (++i < len)
	{
		free(fd[i]);
		ft_check_malloc(fd[i]);
	}
	free(fd);
	free(pid);
}
