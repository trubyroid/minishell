/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_and_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:35:57 by truby             #+#    #+#             */
/*   Updated: 2021/06/17 01:42:06 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

int	add_enviroment_variable(t_all *command, t_env *env)
{
	int	i;
	t_env *new;

	i = -1;
	while (env->next)
		env = env->next;
	new = malloc(sizeof(t_env*));
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

t_env	*delete_enviroment_variable(t_all *command, t_env *env)
{
	size_t	i;
	t_env	*extra;
	t_env	*previous;
	t_env	*first;
	char *key;

	i = 0;
	first = env;
	extra = env;
	previous = extra;
	while (command->arg[1][i] != '\0')
		i++;
	key = ft_strjoin(command->arg[1], "=");
	if (key == NULL)
		return (NULL);
	if (ft_strnstr(env->str, key, ft_strlen(env->str)) != NULL)
	{
		extra = env;
		env = env->next;
		extra->next = NULL;
		free(extra);
		free(key);
		return (env);	
	}
	else
	{
		while (env->next != NULL)
		{
			previous = env;
			env = env->next;
			if (ft_strnstr(env->str, key, ft_strlen(env->str)) != NULL)
			{
				previous->next = env->next;
				env->next = NULL;
				free(env);
				free(key);
				break;
			}
		}
		return (first);
	}
}