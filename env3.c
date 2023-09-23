#include "main.h"

/**
 * exit_error - makes an error message for exit errors.
 * @args: arguments passed to the command.
 *
 * Return: The error string.
 */
char *exit_error(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(hist);
	if (!hist_str)
		return (NULL);

	len = str_len(name) + str_len(hist_str) + str_len(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	str_cpy(error, name);
	str_cat(error, ": ");
	str_cat(error, hist_str);
	str_cat(error, ": exit: Illegal number: ");
	str_cat(error, args[0]);
	str_cat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * _error_126 - makes an error message for permission denied failures.
 * @args: Arguments passed to the command.
 *
 * Return: The error string.
 */
char *_error_126(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(hist);
	if (!hist_str)
		return (NULL);

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
	str_cat(error, ": ");
	str_cat(error, args[0]);
	str_cat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * _error_127 - makes an error message for command not found failures.
 * @args: arguments passed to the command.
 *
 * Return: The error string.
 */
char *_error_127(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(hist);
	if (!hist_str)
		return (NULL);

	len = str_len(name) + str_len(hist_str) + str_len(args[0]) + 16;
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
	str_cat(error, ": not found\n");

	free(hist_str);
	return (error);
}
