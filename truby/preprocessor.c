/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 23:01:58 by truby             #+#    #+#             */
/*   Updated: 2021/07/21 13:34:15 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

// static t_fork	*malloc_and_pipe(t_fork *strct)
// {
// 	int	i;

// 	i = -1;
// 	strct->fd = malloc(sizeof(int *) * strct->len_list);
// 	if (strct->fd == NULL)
// 		return (ft_error_null("Error of malloc.", ENOMEM));
// 	strct->fd[strct->len_list - 1] = NULL;
// 	strct->pid = malloc(sizeof(pid_t) * strct->len_list);
// 	if (strct->pid == NULL)
// 		return (ft_error_null("Error of malloc.", ENOMEM));
// 	while (++i < strct->len_list)
// 	{
// 		strct->fd[i] = malloc(sizeof(int) * 2);
// 		if (strct->fd[i] == NULL)
// 			return (ft_error_null("Error of malloc.", ENOMEM));
// 	}
// 	i = -1;
// 	while (++i < strct->len_list)
// 	{
// 		if (pipe(strct->fd[i]) == -1)
// 			return (ft_error_null("Pipe failed.", errno));
// 	}
// 	return (strct);
// }

// static t_env	*cycle_for_forks(t_all *lst, t_env *env, t_fork *strct, char *home)
// {
// 	write(1, ft_itoa(strct->i), 1);
	// while (lst != NULL && ++strct->i < strct->len_list + 1)
	// {
	// 	write(1, ft_itoa(strct->i), 1);
		// strct->pid[strct->i] = fork();
		// // if (pid[i] < 0)
		// // 	return (ft_error_null("Fork failed.", errno));							//спросить
		// if (strct->pid[strct->i] != 0)
		// 	close(strct->fd[strct->i][1]);
		// else if (strct->pid[strct->i] == 0)
		// {
		// 	if (strct->i == 0)
		// 	{
		// 		close(strct->fd[strct->i][0]);
		// 		dup2(strct->fd[strct->i][1], 1);
		// 	}
		// 	else if (strct->i < strct->len_list - 1)
		// 	{
		// 		close(strct->fd[strct->i - 1][1]);
		// 		dup2(strct->fd[strct->i - 1][0], 0);
		// 		close(strct->fd[strct->i][0]);
		// 		dup2(strct->fd[strct->i][1], 1);
		// 	}
		// 	else 
		// 	{
		// 		close(strct->fd[strct->i - 1][1]);
		// 		dup2(strct->fd[strct->i - 1][0], 0);
		// 	}
		// 	env = processor(lst, env, home, 1);
		// 	exit(errno);
		// }
		// lst = lst->baby_pipe;
	// }
	// strct->i = -1;
	// while (++strct->i < strct->len_list + 1)
	// 	wait(&strct->pid[strct->i]);
	// dup2(strct->fd_0, 0);
// 	return (env);
// }

// static t_env	*init_strct(t_all *command, t_env *env, char *home)
// {
// 	t_fork	*strct;

// 	strct = malloc(sizeof(t_fork *));
// 	if (strct == NULL)
// 		return (ft_error_null("Error of malloc.", ENOMEM));
// 	strct->len_list = babylist_len(command);
// 	strct->i = 5;
// 	strct->fd_0 = dup(0);
// 	strct = malloc_and_pipe(strct);
// 	write(1, ft_itoa(strct->i), 1);
// 	// env = cycle_for_forks(command, env, strct, home);
// 	return (env);
// }

t_env		*preprocessor(t_all *command, t_env *env, char *home)
{
	t_all	*lst;
	pid_t	*pid;
	int		fd_0;
	int 	len;
	int		i;
	int 	**fd;

	if (command->baby_pipe == NULL)
		env = processor(command, env, home, 0);
	else
	{
		// env = init_strct(command, env, home);
		i = -1;
		len = babylist_len(command);
		fd = malloc(sizeof(int *) * len);
		if (!fd)
			return (ft_error_null("Error of malloc.", ENOMEM));
		fd[len - 1] = NULL;
		pid = malloc(sizeof(pid_t) * len);
		if (!pid)
			return (ft_error_null("Error of malloc.", ENOMEM));
		while (++i < len)
		{
			fd[i] = malloc(sizeof(int) * 2);
			if (!fd[i])
				return (ft_error_null("Error of malloc.", ENOMEM));
		}
		i = -1;
		while (++i < len)
		{
			if (pipe(fd[i]) == -1)
				return (ft_error_null("Pipe failed.", errno));
		}
		lst = command;
		i = -1;
		while (lst != NULL && ++i < len + 1)
		{
			pid[i] = fork();
			// if (pid[i] < 0)
			// 	return (ft_error_null("Fork failed.", errno));							//спросить
			if (pid[i] != 0)
				close(fd[i][1]);
			else if (!pid[i])
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
				env = processor(lst, env, home, 1);
				exit(errno);
			}
			lst = lst->baby_pipe;
		}
		i = -1;
		while (++i < len + 1)
			wait(&pid[i]);
		dup2(fd_0, 0);
		// wait_close(command);
	}
	return (env);
}