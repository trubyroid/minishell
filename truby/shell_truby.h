/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_truby.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:57:17 by truby             #+#    #+#             */
/*   Updated: 2021/06/14 21:11:42 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct 	s_env
{
	char				*str;
	struct s_env		*next;
}				t_env;

#include "../shell.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int 	use_cd(char *str);
void 	use_pwd(void);
int 	use_echo(t_all *command);
int		print_env(char **env);
void	print_export(t_env *env);
int		processor(t_all *command, t_env *env);
