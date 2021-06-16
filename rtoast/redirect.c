#include "../shell.h"

void	redirect_flag(t_all *tmp)
{
	int	i;

	i = -1;
	while (tmp->str[++i] != '\0')
		if (tmp->str[i] == '<' || tmp->str[i] == '>')
		{
			tmp->flag_redirect = 1;
			what_is_redirect(tmp);
		}
}

void	what_is_redirect(t_all *tmp)
{
	int	i;

	i = 0;
	while (tmp->str[i] != '<' && tmp->str[i] != '>')
		i++;
	
}

void	one_redirect(t_all *tmp)
{

}