#include "main.h"

/**
 * get_env - To get an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **get_env(const char *var)
{
	int index, len;

	len = str_len(var);
	for (index = 0; environ[index]; index++)
	{
		if (strn_cmp(var, environ[index], len) == 0)
			return (&environ[index]);
	}

	return (NULL);
}

/**
 * env_free - Frees the the environment copy.
 */
void env_free(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}

/**
 * copy_env - makes a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         else - a double pointer to the new copy.
 */
char **copy_env(void)
{
	char **new_environ;
	size_t size;
	int i;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		new_environ[i] = malloc(str_len(environ[i]) + 1);

		if (!new_environ[i])
		{
			for (i--; i >= 0; i--)
				free(new_environ[i]);
			free(new_environ);
			return (NULL);
		}
		str_cpy(new_environ[i], environ[i]);
	}
	new_environ[i] = NULL;

	return (new_environ);
}

/**
 * shell_env - Prints the current environment.
 * @args: arguments passed to the shell.
 * @out: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 */
int shell_env(char **args, char __attribute__((__unused__)) **out)
{
	int index;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], str_len(environ[index]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}

/**
 * shell_setenv - Changes or adds an environmental variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @out: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         else - 0.
 */
int shell_setenv(char **args, char __attribute__((__unused__)) **out)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (get_error(args, -1));

	new_value = malloc(str_len(args[0]) + 1 + str_len(args[1]) + 1);
	if (!new_value)
		return (get_error(args, -1));
	str_cpy(new_value, args[0]);
	str_cat(new_value, "=");
	str_cat(new_value, args[1]);

	env_var = get_env(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (get_error(args, -1));
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];

	free(environ);
	environ = new_environ;
	environ[index] = new_value;
	environ[index + 1] = NULL;

	return (0);
}
