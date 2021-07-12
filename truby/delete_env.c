/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 19:36:30 by truby             #+#    #+#             */
/*   Updated: 2021/07/12 20:12:33 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

static void freeshing(t_env *extra_env, char *key)
{
	extra_env->next = NULL;
	free(extra_env);
	free(key);
	extra_env = NULL;
	key = NULL;
}
static t_env	*first_variable(t_env *env, char *key)
{
	t_env *extra;

	extra = env;
	env = env->next;
	freeshing(extra, key);
	return (env);	
}

static t_env *not_first_variable(t_env *env, char *key)
{
	t_env *previous;
	t_env *first;

	first = env;
	while (env->next != NULL)
	{
		previous = env;
		env = env->next;
		if (ft_strnstr(env->str, key, ft_strlen(env->str)) != NULL)
		{
			previous->next = env->next;
			freeshing(env, key);
			break;
		}
	}
	return (first);
}


t_env	*delete_enviroment_variable(t_all *command, t_env *env)
{
	char *key;

	key = ft_strjoin(command->arg[1], "=");
	if (key == NULL)
		return (NULL);
	if (ft_strnstr(env->str, key, ft_strlen(env->str)) != NULL)
		return (first_variable(env, key));	
	else
		return (not_first_variable(env, key));
}