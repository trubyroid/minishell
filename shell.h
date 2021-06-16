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
		int		num_arg;
		int		flag_dollar;
		int		flag_pipe;
		int		flag_redirect;
		int		ret_$;
		// t_all	*baby_pipe;

}				t_all;

typedef struct		s_env
{
	char			*str;
	struct s_env	*next;
}					t_env;

void	close_minishell(t_env *env);
void	command_name(t_all *tmp);
void	error(int i);
void	prepars(t_all *tmp);
void	arg(t_all *tmp, int i);
int		malloc_arg(t_all *tmp, int i, int num);
int		block_checking(char symbol);
int		quotes_checking(char symbol);
int		skipping_spaces(t_all *tmp, int i);
int		creating_the_first_argument(t_all *tmp, int i, int colnum);
int		creating_next_argument(t_all *tmp, int i, int colnum);
int		amount_of_elements(t_all *tmp, int i, int quotes);
t_env	*creating_list(char **env);
int		quotes_in_quotes(t_all *tmp, int i);

#endif
