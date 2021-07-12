/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 19:36:30 by truby             #+#    #+#             */
/*   Updated: 2021/07/12 21:46:47 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

static void freeshing(t_env *extra_env, char *key, char *second_key)
{
	extra_env->next = NULL;
	free(extra_env);
	free(key);
	free(second_key);
	extra_env = NULL;
	key = NULL;
	second_key = NULL;
}
static t_env	*first_variable(t_env *env, char *key, char *second_key)
{
	t_env *extra;

	extra = env;
	env = env->next;
	freeshing(extra, key, second_key);
	return (env);	
}

static t_env *not_a_first_variable(t_env *env, char *key, char *second_key)
{
	t_env *previous;
	t_env *first;

	first = env;
	while (env->next != NULL)
	{
		previous = env;
		env = env->next;
		if (ft_strnstr(env->str, key, ft_strlen(env->str)) != NULL || (ft_strnstr(env->str, second_key, ft_strlen(second_key)) != NULL && env->str[ft_strlen(second_key)] == '\0'))
		{
			previous->next = env->next;
			freeshing(env, key, second_key);
			break;
		}
	}
	return (first);
}


t_env	*delete_enviroment_variable(t_all *command, t_env *env)
{
	char *key;
	char *second_key;

	second_key = ft_strdup(command->arg[1]);
	key = ft_strjoin(command->arg[1], "=");
	if (key == NULL)
	{
		ft_error("Error of malloc.");
		return (env);
	}
	if (ft_strnstr(env->str, key, ft_strlen(key)) != NULL || (ft_strnstr(env->str, second_key, ft_strlen(second_key)) != NULL && env->str[ft_strlen(second_key)] == '\0'))
		return (first_variable(env, key, second_key));	
	else
		return (not_a_first_variable(env, key, second_key));
}