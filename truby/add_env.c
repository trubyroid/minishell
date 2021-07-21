/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:35:57 by truby             #+#    #+#             */
/*   Updated: 2021/07/21 15:51:54 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

static int	change_str(t_env *env, char *arg_str)
{
	free(env->str);
	env->str = NULL;
	env->str = ft_strdup(arg_str);
	if (!env->str)
		return (ft_error_int("Error of malloc.", ENOMEM, 1));
	return (1);
}

static int	var_with_equal(t_env *env, char *arg_str, int j, int fl)
{
	char	*key;
	char	*key_two;

	key = ft_substr(arg_str, 0, j);
	key_two = ft_substr(arg_str, 0, j - 1);
	if (!key || !key_two)
		return (ft_error_int("Error of malloc.", ENOMEM, 1));
	while (env != NULL)
	{
		if (ft_strnstr(env->str, key, j)
			|| (ft_strnstr(env->str, key_two, j - 1)
				&& env->str[ft_strlen(key_two)] == '\0'))
		{
			fl = change_str(env, arg_str);
			break ;
		}
		env = env->next;
	}
	free(key);
	free(key_two);
	key = NULL;
	key_two = NULL;
	return (fl);
}

static int	var_without_equal(t_env *env, char *arg_str, int fl)
{
	char	*key;

	key = ft_strjoin(arg_str, "=");
	while (env != NULL)
	{
		if (ft_strnstr(env->str, key, ft_strlen(key))
			|| (ft_strnstr(env->str, arg_str, ft_strlen(arg_str))
				&& env->str[ft_strlen(arg_str)] == '\0'))
		{
			fl = 1;
			break ;
		}
		env = env->next;
	}
	free(key);
	key = NULL;
	return (fl);
}

static int	create_new_variable(t_env *env, char *arg_str)
{
	t_env	*new;

	new = malloc(sizeof(t_env *));
	if (!new)
		return (ft_error_int("Error of malloc.", ENOMEM, 1));
	while (env->next != NULL)
		env = env->next;
	env->next = new;
	new->str = ft_strdup(arg_str);
	if (!new->str)
		return (ft_error_int("Error of malloc.", ENOMEM, 1));
	new->next = NULL;
	return (0);
}

int	add_enviroment_variable(t_all *command, t_env *env)
{
	int	j;
	int	q;
	int	fl;

	q = 0;
	fl = 0;
	while (command->arg[++q])
	{
		j = validation(command->arg[q]);
		if (j > 0)
			fl = var_with_equal(env, command->arg[q], j, fl);
		else if (j == 0)
			fl = var_without_equal(env, command->arg[q], fl);
		else if (j < 0)
		{
			write(1, "ya_bash: export: '", 18);
			write(1, command->arg[q], ft_strlen(command->arg[q]));
			ft_error_int("': not a valid identifier", 1, 0);
			continue ;
		}
		if (fl == 0)
			create_new_variable(env, command->arg[q]);
		fl = 0;
	}
	return (0);
}
