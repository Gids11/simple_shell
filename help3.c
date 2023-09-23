#include "main.h"

/**
 * freeargs - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @out: A double pointer to the beginning of args.
 */
void freeargs(char **args, char **out)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(out);
}

/**
 * set_pid - Gets the current process ID.
 *
 * Return: The current process ID or NULL on failure.
 */
char *set_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * set_env_value - Gets the value corresponding to an environmental variable.
 * @start: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 */
char *set_env_value(char *start, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	strn_cat(var, start, len);

	var_addr = get_env(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(str_len(temp) + 1);
		if (replacement)
			str_cpy(replacement, temp);
	}

	return (replacement);
}

/**
 * variable_change - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 */
void variable_change(char **line, int *exe_ret)
{
	int j, k = 0, len;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
				old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replacement = set_pid();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replacement = _itoa_(*exe_ret);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				for (k = j + 1; old_line[k] &&
						old_line[k] != '$' &&
						old_line[k] != ' '; k++)
					;
				len = k - (j + 1);
				replacement = set_env_value(&old_line[j + 1], len);
			}
			new_line = malloc(j + str_len(replacement)
					  + str_len(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			strn_cat(new_line, old_line, j);
			if (replacement)
			{
				str_cat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			str_cat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}
