/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 20:38:02 by truby             #+#    #+#             */
/*   Updated: 2021/07/21 21:55:08 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

char	*ft_strjoin_shell(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	i = -1;
	j = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new == NULL)
		return (NULL);
	while (++i < ft_strlen(s1))
		new[i] = s1[i];
	while (i < ft_strlen(s1) + ft_strlen(s2))
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(s2);
	s2 = NULL;
	return (new);
}

char	*ft_substr_shell(char *s, unsigned int start, size_t len)
{
	char		*b;
	size_t		z;

	z = 1;
	if (s == 0)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	b = (char *)malloc(sizeof(char) * (len + 3));
	if (b == NULL)
		return (NULL);
	b[0] = '"';
	while (z < len)
	{
		b[z] = s[start];
		z++;
		start++;
	}
	b[z] = '"';
	b[++z] = '\0';
	return (b);
}

int	babylist_len(t_all *command)
{
	int	i;

	i = 0;
	while (command != NULL)
	{
		i++;
		command = command->baby_pipe;
	}
	return (i);
}

int	ft_check(t_all *command)
{
	int	i;

	i = -1;
	if (ft_strcmp("env", command->command_name) == 0)
	{
		while (command->arg[++i] != NULL)
		{
			if (ft_strcmp("env", command->arg[i]) != 0)
			{
				write(1, "env: ", 5);
				write(1, command->arg[i], ft_strlen(command->arg[i]));
				return (ft_error_int(": No such file or directory", 127, 0));
			}
		}
	}
	return (1);
}

t_env	*find_variable(t_env *env, char *str, char *str2, int fl)
{
	while (ft_strnstr(env->str, str, ft_strlen(str)) == NULL)
	{
		if (env->next == NULL)
		{
			if (fl == 1)
				write(1, "ya_bash: cd: OLDPWD not set\n", 28);
			if (fl == 2)
			{
				write(1, "ya_bash: ", 9);
				write(1, str2, ft_strlen(str2));
				ft_error_exit(": No such file or directory", 127);
			}
			return (NULL);
		}
		env = env->next;
	}
	return (env);
}
