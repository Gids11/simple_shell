#include "main.h"

/**
 * _open - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */

int _open(char *file_path)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(hist);
	if (!hist_str)
		return (127);

	len = str_len(name) + str_len(hist_str) + str_len(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	str_cpy(error, name);
	str_cat(error, ": ");
	str_cat(error, hist_str);
	str_cat(error, ": Can't open ");
	str_cat(error, file_path);
	str_cat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * proc_commands - Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int proc_commands(char *file_path, int *exe_ret)
{
	ssize_t file, b_read, i;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **out;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = _open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_ret);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = _realloc_(line, old_size, line_size);
		str_cat(line, buffer);
		old_size = line_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	variable_change(&line, exe_ret);
	_handle_line(&line, line_size);
	args = _strtok_(line, " ");
	free(line);
	if (!args)
		return (0);
	if (checkargs(args) != 0)
	{
		*exe_ret = 2;
		freeargs(args, args);
		return (*exe_ret);
	}
	out = args;

	for (i = 0; args[i]; i++)
	{
		if (strn_cmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = callargs(args, out, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}

	ret = callargs(args, out, exe_ret);

	free(out);
	return (ret);
}
