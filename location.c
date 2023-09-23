#include "main.h"

/**
 * _locator - Locates a command in the PATH.
 * @command: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathname of the command.
 */
char *_locator(char *command)
{
	char **path, *temp;
	list_t *dirs, *head;
	struct stat st;

	path = get_env("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = path_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(str_len(dirs->dir) + str_len(command) + 2);
		if (!temp)
			return (NULL);

		str_cpy(temp, dirs->dir);
		str_cat(temp, "/");
		str_cat(temp, command);

		if (stat(temp, &st) == 0)
		{
			free_list_(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	free_list_(head);

	return (NULL);
}

/**
 * _path - Copies path but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *_path(char *path)
{
	int i, length = 0;
	char *path_copy, *pwd;

	pwd = *(get_env("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += str_len(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				str_cat(path_copy, pwd);
				str_cat(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				str_cat(path_copy, ":");
				str_cat(path_copy, pwd);
			}
			else
				str_cat(path_copy, ":");
		}
		else
		{
			strn_cat(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * path_dir - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
list_t *path_dir(char *path)
{
	int index;
	char **dirs, *path_copy;
	list_t *head = NULL;

	path_copy = _path(path);
	if (!path_copy)
		return (NULL);
	dirs = _strtok_(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (index = 0; dirs[index]; index++)
	{
		if (add_node(&head, dirs[index]) == NULL)
		{
			free_list_(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
