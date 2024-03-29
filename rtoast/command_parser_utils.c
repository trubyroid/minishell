#include "../shell.h"

void	for_bash(t_all *tmp)
{
	int		i;
	int		j;
	int		slash;
	char	*temp;

	i = -1;
	j = chek_for_bash(tmp);

	if (j == 0)
		return ;
	slash = j - 1;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(tmp->arg[0]) - (j - 1)));
	while (tmp->arg[0][j] != '\0')
	{
		temp[++i] = tmp->arg[0][j];
		j++;
	}
	temp[i] = '\0';
	free(tmp->arg[0]);
	tmp->arg[0] = temp;

	command_slash(tmp, slash);
}

int	error_cheker(char one, char two, char three)
{
	int	i;

	i = 0;
	if (one == ';')
	{
		error(258, "bash: syntax error near unexpected token");
		return (1);
	}
	if (one == '<' && two == '<' && three == '<')
	{
		error(258, "bash: syntax error near unexpected token `newline'");
		return (1);
	}
	if (one == '>' && two == '>' && three == '>')
	{
		error(258, "bash: syntax error near unexpected token `>'");
		return (1);
	}
	i = error_cheker_one(one, two, three);
	return (i);
}

int	error_cheker_one(char one, char two, char three)
{
	if (one == '>' && two == '<')
	{
		error(258, "bash: syntax error near unexpected token `<'");
		return (1);
	}
	if (one == '<' && two == '>')
	{
		error(258, "bash: syntax error near unexpected token `newline'");
		return (1);
	}
	if (one == '|' && two == '\0')
	{
		error(258, "bash: syntax error near unexpected token `|'");
		return (1);
	}
	if (one == '|' && two == '|')
	{
		error(258, "bash: syntax error near unexpected token `||'");
		return (1);
	}
	if (one == '|' && two == '|' && three == '|')
	{
		error(258, "bash: syntax error near unexpected token `||'");
		return (1);
	}
	return (0);
}

int	chek_for_bash(t_all *tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (tmp->command_name[i] == '.' && tmp->command_name[i + 1] == '/' && \
		tmp->command_name[i + 2] != '\0')
		j = 2;
	if (tmp->command_name[i] == '.' && tmp->command_name[i + 1] == '.' && \
		 tmp->command_name[i + 2] == '/' && tmp->command_name[i + 3] != '\0')
		j = 3;
	return (j);
}
