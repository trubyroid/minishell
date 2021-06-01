#ifndef SHELL_H
# define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct	s_all
{
		char	*str;
		char	*command_name;
		char	**arg;
		int		flag_dollar;
		int		flag_pipe;
		// t_all	*baby;

}				t_all;

typedef struct	s_add
{
	int num;
}				t_add;

void	start(t_all *tmp);
void	command_name(t_all *tmp, int i);
void	error(int i);
void	prepars(t_all *tmp);
void	arg(t_all *tmp, int i);
int		malloc_arg(t_all *tmp, int i, t_add *add);
int		block(t_all *tmp, int i);

#endif
