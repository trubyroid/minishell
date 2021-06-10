#include "shell.h"

int character_checking(char symbol)
{
	int result;

	result = 0;
	if (symbol == ' ')
		result = 1;
	if (symbol == '\'')
		result = 1;
	if (symbol == '\"')
		result = 1;
	return (result);
}
