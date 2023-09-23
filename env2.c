#include "main.h"

/**
 * shell_unsetenv - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @out: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_unsetenv(char **args, char __attribute__((__unused__)) **out)
{
	char **env_var, **new_environ;
	size_t size;
	int index, index2;

	if (!args[0])
		return (get_error(args, -1));
	env_var = get_env(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (get_error(args, -1));

	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (*env_var == environ[index])
		{
			free(*env_var);
			continue;
		}
		new_environ[index2] = environ[index];
		index2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}

/**
 * env_error - Creates an error message for _env errors.
 * @args: arguments passed to the command.
 *
 * Return: The error string.
 */
char *env_error(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(hist);
	if (!hist_str)
		return (NULL);

	args--;
	len = str_len(name) + str_len(hist_str) + str_len(args[0]) + 45;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	str_cpy(error, name);
	str_cat(error, ": ");
	str_cat(error, hist_str);
	str_cat(error, ": ");
	str_cat(error, args[0]);
	str_cat(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * _error_ - makes an error message for _alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *_error_(char **args)
{
	char *error;
	int len;

	len = str_len(name) + str_len(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	str_cpy(error, "alias: ");
	str_cat(error, args[0]);
	str_cat(error, " not found\n");

	return (error);
}

/**
 * syntax_error - generates an error message for syntax errors.
 * @args: Arguments passed to the command.
 *
 * Return: The error string.
 */
char *syntax_error(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(hist);
	if (!hist_str)
		return (NULL);

	len = str_len(name) + str_len(hist_str) + str_len(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	str_cpy(error, name);
	str_cat(error, ": ");
	str_cat(error, hist_str);
	str_cat(error, ": Syntax error: \"");
	str_cat(error, args[0]);
	str_cat(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}

/**
 * cd_error - makes an error message for _cd errors.
 * @args: arguments passed to the command.
 *
 * Return: The error string.
 */
char *cd_error(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(hist);
	if (!hist_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	len = str_len(name) + str_len(hist_str) + str_len(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	str_cpy(error, name);
	str_cat(error, ": ");
	str_cat(error, hist_str);
	if (args[0][0] == '-')
		str_cat(error, ": cd: Illegal option ");
	else
		str_cat(error, ": cd: can't cd to ");
	str_cat(error, args[0]);
	str_cat(error, "\n");

	free(hist_str);
	return (error);
}
