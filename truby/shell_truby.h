/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_truby.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:57:17 by truby             #+#    #+#             */
/*   Updated: 2021/07/26 11:41:26 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_TRUBY_H
# define SHELL_TRUBY_H

# include "../shell.h"
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include<sys/types.h>
# include<sys/wait.h>

typedef struct s_fork
{
	pid_t	*pid;
	int		**fd;
	int		len_list;
	int		fd_0;
	int		i;
}				t_fork;

void	use_cd(t_env *env, char **dir, char *root);
void	use_pwd(t_all *command);
void	implementation(t_all *command, t_env *env);
void	use_echo(t_all *command);
void	print_env(t_all *command, t_env *env);
void	print_export(t_all *command, t_env *env);
char	*ft_strjoin_shell(char *s1, char *s2);
t_env	*processor(t_all *command, t_env *env, char *home, int fl);
int		add_enviroment_variable(t_all *command, t_env *env);
t_env	*delete_enviroment_variable(t_all *command, t_env *env);
void	print_or_add(t_all *command, t_env *env);
void	fork_exec(t_all *command, t_env *env, int fl);
void	ft_error(char *str, int i);
int		ft_error_int(char *str, int i, int fl);
void	*ft_error_null(char *str, int i);
void	ft_error_exit(char *str, int i);
char	*ft_substr_shell(char *s, unsigned int start, size_t len);
t_env	*preprocessor(t_all *command, t_env *env);
void	wait_close(t_all *command);
int		babylist_len(t_all *command);
int		ft_check(t_all *command);
t_env	*find_variable(t_env *env, char *str, char *str2, int fl);
int		validation(char *arg_str);
char	**create_massiv(t_env *env);
void	free_massives(char **paths, char **env_massiv, char *pwd, int fl);
void	close_dup(t_all *command);
t_env	*copy_lst(t_env *env);

#endif
