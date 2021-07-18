/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_truby.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:57:17 by truby             #+#    #+#             */
/*   Updated: 2021/07/18 18:43:54 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

void 	use_cd(t_env *env, char **dir, char *root);
void 	use_pwd(t_all *command);
void	exec(t_all *command, t_env *env);
void 	use_echo(t_all *command);
void	print_env(t_env *env);
void	print_export(t_env *env);
char	*ft_strjoin_shell(char *s1, char *s2);
t_env	*processor(t_all *command, t_env *env, char *root);
int		add_enviroment_variable(t_all *command, t_env *env);
t_env	*delete_enviroment_variable(t_all *command, t_env *env);
void	ft_export(t_all *command, t_env *env);
void	implementation(t_all *command, t_env *env);
void	ft_error(char *str);
int		ft_error_int(char *str);
void	*ft_error_null(char *str);
char	*ft_substr_shell(char *s, unsigned int start, size_t len);
t_env	*preprocessor(t_all *command, t_env *env, char *home);
void	wait_close(t_all *command);
int		babylist_len(t_all *command);
int		ft_check(t_all *command);
