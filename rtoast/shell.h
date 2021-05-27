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
		char	**key;
		int		flag_pipe;

}				t_all;

void	start(t_all *tmp);
void	command_name(t_all *tmp, int i);
void	error(int i);
void	prepars(t_all *tmp);

#endif
