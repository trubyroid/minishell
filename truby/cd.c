#include "shell_truby.h"

// int g_status;

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*b;
	size_t		z;

	z = 0;
	if (s == 0)
		return (NULL);
	if (start >= strlen(s))
		len = 0;
	b = (char *)malloc(sizeof(char) * (len + 1));
	if (b == NULL)
		return (NULL);
	while (z < len)
	{
		b[z] = s[start];
		z++;
		start++;
	}
	b[z] = '\0';
	return (b);
}

static void change_dir(char **dir)
{
	char *pwd;
	char *new_str;
	int	i;
	int fl;

	pwd = NULL;
	new_str = NULL;
	i = -1;
	fl = 0;
	if (dir == NULL || strcmp("~", dir[1]) == 0)
	{
		pwd = getcwd(pwd, 0);
		while (pwd[++i] != '\0')
		{
			if (pwd[i] == '/')
				fl++;
			if (fl == 3)
			{
				new_str = ft_substr(pwd, 0, i);
				break ;
			}
		}
		chdir(new_str);
		free(new_str);
		free(pwd);
	}
	else if (chdir(dir[0]) == -1)
	{
		printf("cd: %s: %s\n", strerror(errno), dir[0]);
		// g_status = 1;
	}
}

int use_cd(char **str)
{
	int i;
	char *dir = NULL;

	change_dir(str);		//перемещает
	dir = getcwd(dir, 0);   //определяет нынешнюю директорию
	printf("%s\n", dir);    // показывает, что было осуществлено перемещение
	free(dir);
	return (0);
}