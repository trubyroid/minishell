#include "shell_truby.h"

t_env		*processor(t_all *command, t_env *env)
{
	if (strcmp("env", command->command_name) == 0)
		print_env(env);
	else if (strcmp("echo", command->command_name) == 0)
		use_echo(command);
	else if (strcmp("pwd", command->command_name) == 0)
		use_pwd();
	else if (strcmp("unset", command->command_name) == 0)
		env = delete_enviroment_variable(command, env);
	else if (strcmp("cd", command->command_name) == 0)
	{
		use_cd(command->arg);
	}
	else if (strcmp("exit", command->command_name) == 0)
		close_minishell(env);
	else if (strcmp("export", command->command_name) == 0)
	{
		if (command->arg == NULL)
			print_export(env);
		else
			add_enviroment_variable(command, env);
	}
	// else
	// {
	// 	execve();
	// }
	return (env);
}