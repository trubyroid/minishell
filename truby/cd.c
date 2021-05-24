#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int i;
	char *dir = NULL;
	size_t len;

	i = chdir("..");   //перемещает
	while (!dir)
		dir = getcwd(dir, ++len);   //определяет нынешнюю директорию
	printf("%s\n", dir);    // показывает, что было осуществлено перемещение
	return (0);
}