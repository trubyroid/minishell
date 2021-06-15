#include "shell_truby.h"

// int g_status;

static void change_dir(char *dir)
{
	// if (dir == NULL)
	// {
	// 	if (chdir("..") == -1)
	// 	{
	// 		printf("cd: %s: %s\n", strerror(errno), dir);
	// 		g_status = 1;
	// 	}
	// }
	if (chdir(dir) == -1)
	{
		printf("cd: %s: %s\n", strerror(errno), dir);
		// g_status = 1;
	}
}

int use_cd(char *str)
{
	int i;
	char *dir = NULL;

	change_dir(str);		//перемещает
	dir = getcwd(dir, 0);   //определяет нынешнюю директорию
	printf("%s\n", dir);    // показывает, что было осуществлено перемещение
	free(dir);
	return (0);
}