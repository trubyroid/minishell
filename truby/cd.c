#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int g_status;

void change_dir(char *dir)
{
	if (chdir(dir) == -1)
	{
		printf("cd: %s: %s\n", strerror(errno), dir);
		g_status = 1;
	}
}

int main(void)
{
	int i;
	char *dir = NULL;

	change_dir("..");		//перемещает
	dir = getcwd(dir, 0);   //определяет нынешнюю директорию
	printf("%s\n", dir);    // показывает, что было осуществлено перемещение
	free(dir);
	return (0);
}