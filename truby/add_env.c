/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:35:57 by truby             #+#    #+#             */
/*   Updated: 2021/07/12 19:39:17 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

static int	ft_check(t_all *command)
{
	int i;
	
	i = 0;
	while (command->arg[1][i] != '=' && command->arg[1][i])
	{
		// if (ft_isdigit(command->arg[1][i]))
		// 	return (-1);
		i++;
	}
	if (command->arg[1][i] == '=')
		return (i + 1);
	return (0);
}

int	add_enviroment_variable(t_all *command, t_env *env)						//проработать кейс с ключом без значения
{
	int	i;
	int j;
	t_env *new;
	char *key;
	char *key_two;

	i = -1;
	j = ft_check(command);
	if (j > 0)
	{
		key = ft_substr(command->arg[1], 0, j);
		key_two = ft_substr(command->arg[1], 0, j - 1);
		while (env->str)
		{
			if (ft_strnstr(env->str, key, j))
			{
				free(env->str);
				env->str = NULL;
				env->str = ft_strdup(command->arg[1]);
				free(key);
				free(key_two);
				key = NULL;
				key_two = NULL;
				return (0);
			}
			else if (ft_strnstr(env->str, key_two, j - 1) && env->str[ft_strlen(key_two)] == '\0')
			{
				free(env->str);
				env->str = NULL;
				env->str = ft_strdup(command->arg[1]);
				free(key);
				free(key_two);
				key = NULL;
				key_two = NULL;
				return (0);
			}
			if (env->next == NULL)
				break ;
			env = env->next;
		}
		free(key);
		free(key_two);
		key = NULL;
		key_two = NULL;
	}
	else if (j == 0)
	{
		while (env->str)
		{
			if (ft_strnstr(env->str, command->arg[1], ft_strlen(command->arg[1])) && env->str[ft_strlen(command->arg[1])] == '\0')
				return (0);
			if (env->next == NULL)
				break ;
			env = env->next;
		}
	}
	// else if (j < 0)
	// {
	// 	error
	// }
	new = malloc(sizeof(t_env *));
	if (!new)
		return (-1);										//error
	env->next = new;
	new->str = malloc(sizeof(char) * ft_strlen(command->arg[1]));
	if (!new->str)
		return (-1);
	while (command->arg[1][++i] != '\0')
		new->str[i] = command->arg[1][i];
	new->str[i] = '\0';
	new->next = NULL;
	return (0);
}
