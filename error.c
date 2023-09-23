#include "main.h"

/**
 * _lent - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int _lent(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 /= 10;
	}

	return (len);
}

/**
 * _itoa_ - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *_itoa_(int num)
{
	char *buffer;
	int len = _lent(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}


/**
 * get_error - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int get_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = env_error(args);
		break;
	case 1:
		error = _error_(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = exit_error(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = syntax_error(args);
		else
			error = cd_error(args);
		break;
	case 126:
		error = _error_126(args);
		break;
	case 127:
		error = _error_127(args);
		break;
	}
	write(STDERR_FILENO, error, str_len(error));

	if (error)
		free(error);
	return (err);

}
