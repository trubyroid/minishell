#include "../shell.h"

void	error(int i, char *str)
{
		g_status = i;
		printf("%s\n", str);
}

int		prepars(t_all *tmp)
{
	int cod;
	tmp->colnum_fd = 0;
	tmp->massiv_fd = NULL;
	tmp->baby_pipe = NULL;
	tmp->fd_out = 1;
	tmp->fd_in = 0;
	tmp->arg = NULL;
	tmp->num_arg = 0;
	tmp->command_name = NULL;
	tmp->file_name = NULL;
	tmp->redirect_i = 0;
	cod = syntax_error(tmp);
	cod = cod - quotes_error(tmp);
	if (tmp->str != NULL)
	{
		one_symbol(tmp);
		redirect_pars(tmp);
		dollar_parser(tmp);
	}
	return (cod);
}

void	dollar_parser(t_all *tmp)
{
	int i;

	i = 0;
	while(tmp->str[i] != '\0')
	{
		if (tmp->str[i] == '\'')
		{
			i++;
			while (tmp->str[i] != '\'' && tmp->str[i] != '\0')
				i++;
		}
		if (tmp->str[i] == '$')
		{
			if (tmp->str[i + 1] == '!' || tmp->str[i + 1] == '$' || tmp->str[i + 1] == '*')
			{
				i = remove_symbol(tmp, i);
				i = remove_symbol(tmp, i);
				add_spase(i, tmp);
			}
			if (tmp->str[i + 1] == '#' || tmp->str[i + 1] == '@' || tmp->str[i + 1] == '-')
			{
				i = remove_symbol(tmp, i);
				i = remove_symbol(tmp, i);
				add_spase(i, tmp);
			}
			if((tmp->str[i + 1] >= '0' && tmp->str[i + 1] <= '9') && tmp->str[i + 2] == ' ')
			{
				i = remove_symbol(tmp, i);
				i = remove_symbol(tmp, i);
				add_spase(i, tmp);
			}
			if (tmp->str[i] != '$' && (check_for_dollar(tmp->str[i + 1]) != 0))
				i++;
		}
		if(tmp->str[i] == '$' && tmp->str[i + 1] == '$')
		{
			i = remove_symbol(tmp, i);
			i = remove_symbol(tmp, i);
			add_spase(i, tmp);
		}
		i++;
	}
}

void	redirect_pars(t_all *tmp)
{
	int i;

	i = 0;
	i = skipping_spaces(tmp, i);
	if (tmp->str[i] == '>' || tmp->str[i] == '<')
		tmp->redirect_i = redirect(tmp, i);
}

int	syntax_error(t_all *tmp)
{
	int i;

	i = 0;
	while (tmp->str[i] != '\0')
	{
		if (tmp->str[i] == '\'')
		{
			i++;
			while (tmp->str[i] != '\'')
				i++;
		}
		if (tmp->str[i] == '\"')
		{
			i++;
			while (tmp->str[i] != '\"')
				i++;
		}
		if (tmp->str[i] == ';' && tmp->str[i + 1] == ';')
		{
			error(258, "bash: syntax error near unexpected token `;;'");
			return (1);
		}
		if (tmp->str[i] == '<' && tmp->str[i + 1] == '<' && tmp->str[i + 2] == '<')
		{
			error(258, "bash: syntax error near unexpected token `newline'");
			return (1);
		}
		if (tmp->str[i] == '>' && tmp->str[i + 1] == '>' && tmp->str[i + 2] == '>')
		{
			error(258, "bash: syntax error near unexpected token `>'");
			return (1);
		}
		if (tmp->str[i] == '>' && tmp->str[i + 1] == '<')
		{
			error(258, "bash: syntax error near unexpected token `<'");
			return (1);
		}
		if (tmp->str[i] == '<' && tmp->str[i + 1] == '>')
		{
			error(258, "bash: syntax error near unexpected token `newline'");
			return (1);
		}
		if (tmp->str[i] == '|' && tmp->str[i + 1] == '|' && tmp->str [i + 2] != '|')
		{
			i = remove_symbol(tmp, i);
			i = remove_symbol(tmp, i);
		}
		if (tmp->str[i] == '|' && tmp->str[i + 1] == '|' && tmp->str [i + 2] == '|')
		{
			error(258, "bash: syntax error near unexpected token `||'");
			return (1);
		}
		i++;
	}
	if (i > 0 && tmp->str[i - 1] == '\\')
	{
		error(258, "bash: syntax error near unexpected token `\'");
		return (1);
	}
	return (0);
}

int	quotes_error(t_all *tmp)
{
	int i;

	i = 0;
	while (tmp->str[i] != '\0')
	{
		if (tmp->str[i] == '\'')
		{
			i++;
			while (tmp->str[i] != '\'' && tmp->str[i] != '\0')
				i++;
			if (tmp->str[i] == '\0')
			{
				error(1, "bash: syntax error near unexpected token quotes");
				return (1);
			}
		}
		if (tmp->str[i] == '\"')
		{
			i++;
			while (tmp->str[i] != '\"' && tmp->str[i] != '\0')
				i++;
			if (tmp->str[i] == '\0')
			{
				error(1, "bash: syntax error near unexpected token quotes");
				return (1);
			}
		}
		i++;
	}
	return(0);
}

void add_spase(int i, t_all *tmp)
{
	char *temp;
	int j;
	int rem;

	j = ft_strlen(tmp->str) + 1;
	if (i != (j - 2))
	{
		temp = (char *)malloc(sizeof(char) * (j + 1));
		temp[j] = '\0';
		j = -1;
		while (++j < i)
			temp[j] = tmp->str[j];
		temp[j] = ' ';
		while (tmp->str[i] != '\0')
		{
			temp[++j] = tmp->str[i];
			i++;
		}
		free(tmp->str);
		tmp->str = temp;
	}
}

void one_symbol(t_all *tmp)
{
	int i;

	i = 0;
	while (tmp->str[i] != '\0')
	{
		if (tmp->str[i] == '\'')
		{
			i++;
			while (tmp->str[i] != '\'')
				i++;
		}
		if (tmp->str[i] == '\"')
		{
			i++;
			while (tmp->str[i] != '\"')
				i++;
		}
		if (tmp->str[i] == '&')
			error(258, "bash: syntax error near unexpected token `&'");
		if (tmp->str[i] == ')' && tmp->str[i + 1] == '(')
			error(258, "bash: syntax error near unexpected token `)'");
		i++;
	}
}
