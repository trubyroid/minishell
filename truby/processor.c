#include "shell_truby.h"

int		processor(t_all *command, t_env *env)
{
	if (strcmp("env", command->command_name) == 0)
		print_env(env);
	if (strcmp("echo", command->command_name) == 0)
		use_echo(command);
	if (strcmp("pwd", command->command_name) == 0)
		use_pwd();
	// if (strcmp("unset", command->command_name) == 0)
	// 	delete_enviroment_variable(env);				//create a function
	if (strcmp("cd", command->command_name) == 0)
	{
		use_cd(command->arg[1]);
	}
	if (strcmp("exit", command->command_name) == 0)
		exit(0);
	if (strcmp("export", command->command_name) == 0)
	{
		if (command->arg == NULL)
			print_export(env);
		//else
			//add_enviroment_variable(env);				//create a function
	}
	return (0);
}