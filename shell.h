#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "./libft/libft.h"
# include "./libft/get_next_line.h"
# include "readline/readline.h"
# include "readline/history.h"

# define ANSI_COLOR_RED		"\x1b[31m"
# define ANSI_COLOR_GREEN	"\x1b[32m"
# define ANSI_COLOR_YELLOW	"\x1b[33m"
# define ANSI_COLOR_BLUE	"\x1b[34m"
# define ANSI_COLOR_MAGENTA	"\x1b[35m"
# define ANSI_COLOR_CYAN	"\x1b[36m"
# define ANSI_COLOR_RESET	"\x1b[0m"

int	error_cod;

typedef struct s_all
{
	char			*str;
	char			*command_name;
	char			**arg;
	char			*file_name;
	int				*massiv_fd;
	int				fd_pipe[2];
	int				colnum_fd;
	int				num_arg;
	int				fd_out;
	int				fd_in;
	int				redirect_i;
	int				ret_dollar;
	struct s_all	*baby_pipe;
}				t_all;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}					t_env;

typedef struct s_hist
{
	char			*str;
	struct s_hist	*next;
}					t_hist;

void	close_minishell(t_env *env, char *home);
void	command_name(t_all *tmp, t_env *lst, int i);
void	error(int i, char *str);
int		prepars(t_all *tmp);
void	arg(t_all *tmp, int i, t_env *lst);
int		block_checking(char symbol);
int		quotes_checking(char symbol);
int		skipping_spaces(t_all *tmp, int i);
void	creating_name_argument(t_all *tmp);
int		creating_next_argument(t_all *tmp, int i, int colnum, t_env *lst);
int		amount_of_elements(t_all *tmp, int i, int quotes);
t_env	*creating_list(char **env);
int		quotes_in_quotes(t_all *tmp, int i);
int		check_for_dollar(char symbol);
int		dollar_make(char **str, int i, t_env *lst);
void	create_new_str(char **str, char *original, char *replaced, int i);
void	dollar_parser(t_all *tmp);
int		argc_amount_of_elements(t_all *tmp, int i);
int		argc_amout_of_elements(t_all *tmp, int i);
void	remove_quotes(t_all *tmp, int i);
int		remove_symbol_arguments(t_all *tmp, int i, int s);
int		redirect(t_all *tmp, int i);
void	redirect_pars(t_all *tmp);
int		double_redirect(t_all *tmp, int i);
char	**list_in_massiv(t_env *lst, char **env);
int		list_size(t_env	*lst);
void	creating_file_name_elem(t_all *tmp);
int		reverse_redirect(t_all *tmp, int i);
void	conrol_d(void);
int		single_redirect(t_all *tmp, int i);
int		reverse_double_redirect(t_all *tmp, int i);
int		special_dollar(t_all *tmp, int i);
int		remove_symbol(t_all *tmp, int i);
char	*find_original(char *str, int i);
void	cycle(t_all *tmp, t_env *lst);
char	*find_home(void);
char	*substitution(char *original, t_env *lst);
void	free_all(t_all *tmp);
void	search_dollar(t_all *tmp, t_env *lst);
void	bias(t_all *tmp, int i);
int		syntax_error(t_all *tmp);
int		quotes_error(t_all *tmp);
int		chek_dollar_quotes(char *str, int i);
void	add_spase(int i, t_all *tmp);
void	for_bash(t_all *tmp);
void	add_fd(t_all *tmp, int fd);
int		remove_symbol_name(t_all *tmp, int i);
void	quotes_name(t_all *tmp);
t_all	*init_baby(t_all *baby, t_all *tmp);
void	one_symbol(t_all *tmp);

#endif
