/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 14:45:19 by truby             #+#    #+#             */
/*   Updated: 2021/07/23 21:23:29 by truby            ###   ########.fr       */
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
	int		j = 0;
	int		o = 0;
	int		g = 0;

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
	if (command->arg[1] != NULL)
	{
		i++;
		if (ft_isdigit(command->arg[1][i]) || command->arg[1][i] == '-')
		{
			if (command->arg[2] == NULL)
			{
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
				g = ft_atoi(command->arg[1]);								//добавить обновление счетчика
				if (g >= 0)
				{
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
