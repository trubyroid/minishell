#include "shell_truby.h"

// int g_status;

static void change_dir(char **dir)
{
	char *str;
	int	i;
	int fl;

	str = NULL;
	i = -1;
	i = 0;
	if (dir == NULL)
	{
		str = getcwd(str, 0);
		while (str[++i] != "\0")
		{
			if (str[i] == '/')
				fl++;
			if (fl == 3)
				ft_substr(str, 0, i);
		}
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