/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_and_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:35:57 by truby             #+#    #+#             */
/*   Updated: 2021/06/16 22:25:23 by truby            ###   ########.fr       */
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
	new->str = malloc(sizeof(char) * strlen(command->arg[1]));
	if (!new->str)
		return (-1);
	while (command->arg[1][++i] != '\0')
		new->str[i] = command->arg[1][i];
	new->str[i] = '\0';
	new->next = NULL;
	return (0);
}

// int	delete_enviroment_variable(t_all *command, t_env *env)
// {
// 	size_t	i;
// 	char *key;

// 	i = 0;
// 	while (command->arg[1][i] != '=')
// 		i++;
// 	key = ft_substr(command->arg[1], 0, i++);
// 	if (key == NULL)
// 		return (-1);
// 	while (env->str)
// 	{
// 		if (ft_strnstr(env->str, key, strlen(env->str)) != NULL)


// 	}

// }