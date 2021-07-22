#include "../shell.h"

void	ctrl_c(int i)
{
	rl_on_new_line();
	rl_redisplay();
	write(1, "\e[0K\n", 6);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_slash(int i)
{
	rl_on_new_line();
	rl_redisplay();
	write(1, "\e[0K", 5);
}

int	skipping_spaces(t_all *tmp, int i)
{
	while (tmp->str[i] == ' ')
		i++;
	return (i);
}

int	quotes_checking(char symbol)
{
	int	result;

	result = 0;
	if (symbol == '\'')
		result = 1;
	if (symbol == '\"')
		result = 2;
	return (result);
}
