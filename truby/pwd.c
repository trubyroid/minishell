#include "shell_truby.h"

void use_pwd(void)
{
	char *dir = NULL;

	dir = getcwd(dir, 0);
	printf("%s\n", dir);
	free(dir);
	return 0;
}