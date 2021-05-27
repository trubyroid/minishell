#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *dir = NULL;

	dir = getcwd(dir, 0);
	printf("%s\n", dir);
	free(dir);
	return 0;
}