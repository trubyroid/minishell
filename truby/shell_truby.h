/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_truby.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:57:17 by truby             #+#    #+#             */
/*   Updated: 2021/06/16 22:01:30 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int 	use_cd(char **str);
void 	use_pwd(void);
int 	use_echo(t_all *command);
int		print_env(t_env *env);
void	print_export(t_env *env);
int		processor(t_all *command, t_env *env);
int		add_enviroment_variable(t_all *command, t_env *env);
int		delete_enviroment_variable(t_all *command, t_env *env);
char	*ft_substr(char const *s, unsigned int start, size_t len);
