#include "shell_truby.h"

void use_pwd(void)
{
	char *dir = NULL;

	dir = getcwd(NULL, 0);
	printf("%s\n", dir);
	free(dir);
	dir = NULL;
}