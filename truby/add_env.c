/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:35:57 by truby             #+#    #+#             */
/*   Updated: 2021/07/14 20:30:41 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

static int	ft_check(t_all *command, int q)
{
	int i;
	int	k;
	
	i = 1;
	if (!ft_isalpha(command->arg[q][0]) && command->arg[q][k] != '_')
		return (-1);
	while (command->arg[q][i] != '=' && command->arg[q][i])
	{
		if (!ft_isalnum(command->arg[1][i]))
			return (-1);
		i++;
	}
	k = i;
	while(command->arg[q][++k] != '\0')
	{
		if (command->arg[q][k] < 42 && command->arg[q][k] > 57 && command->arg[q][k] < 63)
			return (-1);
	}
	if (command->arg[q][i] == '=')
		return (i + 1);
	return (0);
}

int	add_enviroment_variable(t_all *command, t_env *env)						//проработать кейс с ключом без значения
{
	int	i;
	int j;
	int q;
	int fl;
	t_env *new;
	char *key;
	char *key_two;

	q = 0;
	fl = 0;
	while (command->arg[++q])
	{
		i = -1;
		j = ft_check(command, q);
		if (j > 0)
		{
			key = ft_substr(command->arg[q], 0, j);
			key_two = ft_substr(command->arg[q], 0, j - 1);
			while (env->str)
			{
				if (ft_strnstr(env->str, key, j))
				{
					free(env->str);
					env->str = NULL;
					env->str = ft_strdup(command->arg[q]);
					fl = 1;
					break ;
				}
				else if (ft_strnstr(env->str, key_two, j - 1) && env->str[ft_strlen(key_two)] == '\0')
				{
					free(env->str);
					env->str = NULL;
					env->str = ft_strdup(command->arg[q]);
					fl = 1;
					break ;
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
				if (ft_strnstr(env->str, command->arg[q], ft_strlen(command->arg[q])) && env->str[ft_strlen(command->arg[q])] == '\0')
				{
					fl = 1;
					break ;
				}
				if (env->next == NULL)
					break ;
				env = env->next;
			}
		}
		else if (j < 0)
		{
			write(1, "ya_bash: export: '", 18);
			write(1, command->arg[q], ft_strlen(command->arg[q]));
			ft_error_int("': not a valid identifier ");
			break ;
		}
		if (fl == 0)
		{
			new = malloc(sizeof(t_env *));
			if (!new)
				return (-1);										//error
			env->next = new;
			new->str = malloc(sizeof(char) * ft_strlen(command->arg[q]));
			if (!new->str)
				return (-1);
			while (command->arg[q][++i] != '\0')
				new->str[i] = command->arg[q][i];
			new->str[i] = '\0';
			new->next = NULL;
		}
		fl = 0;
	}
	return (0);
}
