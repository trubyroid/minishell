#include "shell_truby.h"

t_env		*processor(t_all *command, t_env *env, char *root)
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
		use_cd(command->arg, root);
	}
	else if (strcmp("exit", command->command_name) == 0)
		close_minishell(env, root);
	else if (strcmp("export", command->command_name) == 0)
	{
		if (command->arg[1] == NULL)
			print_export(env);
		else
			add_enviroment_variable(command, env);
	}
	else
	{
		exec(command, env);
	}
	return (env);
}