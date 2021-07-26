/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 23:01:58 by truby             #+#    #+#             */
/*   Updated: 2021/07/26 14:06:58 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

static int	**dup_close(int i, int **fd, int len)
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
	return (fd);
}

static void	cycle_if_pipe(t_all *command, t_env *env, pid_t *pid, int **fd)
{
	int		len;
	int		i;
	t_all	*lst;

	len = babylist_len(command);
	i = -1;
	lst = command;
	while (lst != NULL && ++i < len + 1)
	{
		pid[i] = fork();
		if (pid[i] != 0)
			close(fd[i][1]);
		else if (!pid[i])
		{
			fd = dup_close(i, fd, len);
			env = processor(lst, env, command->home, 1);
			exit(errno);
		}
		lst = lst->baby_pipe;
	}
	post_work(len, pid, fd);
}

static void	ft_if_pipe(t_all *command, t_env *env)
{
	int		len;
	int		**fd;
	pid_t	*pid;
	int		i;

	i = -1;
	len = babylist_len(command);
	fd = malloc(sizeof(int *) * len);
	ft_check_malloc(fd);
	fd[len - 1] = NULL;
	pid = malloc(sizeof(pid_t) * len);
	ft_check_malloc(pid);
	while (++i < len)
	{
		fd[i] = malloc(sizeof(int) * 2);
		ft_check_malloc(fd[i]);
	}
	i = -1;
	while (++i < len)
	{
		if (pipe(fd[i]) == -1)
			return (ft_error_exit("Pipe failed.", errno));
	}
	cycle_if_pipe(command, env, pid, fd);
}

t_env	*preprocessor(t_all *command, t_env *env)
{
	int		fd_0;
	int		len;
	int		i;
	int		**fd;

	fd_0 = dup(0);
	if (command->baby_pipe == NULL)
		env = processor(command, env, command->home, 0);
	else
		ft_if_pipe(command, env);
	dup2(fd_0, 0);
	if (command->home)
		free(command->home);
	command->home = NULL;
	return (env);
}
