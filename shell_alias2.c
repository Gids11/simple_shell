#include "main.h"


/**
 * set_builtin - Matches a command with a corresponding function.
 * @command: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*set_builtin(char *command))(char **args, char **out)
{
	builtin_t funcs[] = {
		{ "exit", shell_exit },
		{ "env", shell_env },
		{ "setenv", shell_setenv },
		{ "unsetenv", shell_unsetenv },
		{ "cd", shell_cd },
		{ "alias", shell_alias },
		{ "help", shell_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (str_cmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * shell_exit - Causes normal process termination
 *                for the shellby shell.
 * @args: An array of arguments containing the exit value.
 * @out: A double pointer to the beginning of args.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 */
int shell_exit(char **args, char **out)
{
	int i, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (get_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (get_error(--args, 2));
	args -= 1;
	freeargs(args, out);
	env_free();
	freealias(aliases);
	exit(num);
}

/**
 * shell_cd - Changes the current directory of the shellby process.
 * @args: An array of arguments.
 * @out: A double pointer to the beginning of args.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_cd(char **args, char __attribute__((__unused__)) **out)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || str_cmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (get_env("OLDPWD") != NULL)
					(chdir(*get_env("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (get_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (get_error(args, 2));
			}
		}
	}
	else
	{
		if (get_env("HOME") != NULL)
			chdir(*(get_env("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (shell_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shell_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, str_len(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * shell_help - Displays information about builtin commands.
 * @args: An array of arguments.
 * @front: A pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_help(char **args, char __attribute__((__unused__)) **out)
{
	if (!args[0])
		_all();
	else if (str_cmp(args[0], "alias") == 0)
		_alias();
	else if (str_cmp(args[0], "cd") == 0)
		_cd();
	else if (str_cmp(args[0], "exit") == 0)
		_exit_();
	else if (str_cmp(args[0], "env") == 0)
		_env();
	else if (str_cmp(args[0], "setenv") == 0)
		_setenv();
	else if (str_cmp(args[0], "unsetenv") == 0)
		_unsetenv();
	else if (str_cmp(args[0], "help") == 0)
		_help();
	else
		write(STDERR_FILENO, name, str_len(name));

	return (0);
}
