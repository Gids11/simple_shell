#include "main.h"

void sig_args(int s);
int exec(char **args, char **out);

/**
 * sig_args - provides signal upon prompt
 * @s: signal
 */
void sig_args(int s)
{
	char *prompt = "\n$ ";

	(void)(s);
	signal(SIGINT, sig_args);
	write(STDIN_FILENO, prompt, 3);
}

/**
 * exec - Executes a command in a child process.
 * @args: An array of arguments.
 * @out: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int exec(char **args, char **out)
{
	pid_t child_pid;
	int status, flagging = 0, ret = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flagging = 1;
		command = _locator(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (get_error(args, 126));
		else
			ret = (get_error(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flagging)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
				ret = (get_error(args, 126));
			env_free();
			freeargs(args, out);
			freealias(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flagging)
		free(command);
	return (ret);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *exe_ret = &retn;
	char *prompt = "$ ", *_new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, sig_args);

	*exe_ret = 0;
	environ = copy_env();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = proc_commands(argv[1], exe_ret);
		env_free();
		freealias(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = args_handler(exe_ret);
		env_free();
		freealias(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = args_handler(exe_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, _new_line, 1);
			env_free();
			freealias(aliases);
			exit(*exe_ret);
		}
	}

	env_free();
	freealias(aliases);
	return (*exe_ret);
}
