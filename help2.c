#include "main.h"

/**
 * _env - Displays information on 'env'.
 */
void _env(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, str_len(msg));
}

/**
 * _setenv - Displays information on 'setenv'.
 */
void _setenv(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, str_len(msg));
}

/**
 * _unsetenv - Displays information on 'unsetenv'.
 */
void _unsetenv(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, str_len(msg));
}
