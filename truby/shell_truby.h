/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_truby.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:57:17 by truby             #+#    #+#             */
/*   Updated: 2021/06/28 19:08:22 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int 	use_cd(t_env *env, char **dir, char *root);
void 	use_pwd(void);
void	exec(t_all *command, t_env *env);
int 	use_echo(t_all *command);
int		print_env(t_env *env);
void	print_export(t_env *env);
void	change_env(t_env *env);
char	*ft_strjoin_shell(char *s1, char *s2);
t_env	*processor(t_all *command, t_env *env, char *root);
int		add_enviroment_variable(t_all *command, t_env *env);
t_env	*delete_enviroment_variable(t_all *command, t_env *env);
