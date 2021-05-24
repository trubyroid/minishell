#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *dir = NULL;
	size_t len = 0;

	while (!dir)
		dir = getcwd(dir, ++len);
	printf("%s\n", dir);
	return 0;
}