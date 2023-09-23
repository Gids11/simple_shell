#include "main.h"

/**
 * shell_alias - prints all aliases, specific aliases, or sets an alias.
 * @args: An array of arguments.
 * @out: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         else - 0.
 */
int shell_alias(char **args, char __attribute__((__unused__)) **out)
{
	alias_t *temp = aliases;
	int i, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			alias_print(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		value = str_chr(args[i], '=');
		if (!value)
		{
			while (temp)
			{
				if (str_cmp(args[i], temp->name) == 0)
				{
					alias_print(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = get_error(args + i, 1);
		}
		else
			fix_alias(args[i], value);
	}
	return (ret);
}

/**
 * fix_alias - Will either set an existing alias 'name' with a new value
 * @var_name: Name of the alias.
 * @value: Value of the alias. First character is a '='.
 */
void fix_alias(char *var_name, char *value)
{
	alias_t *temp = aliases;
	int len, j, k;
	char *new_value;

	*value = '\0';
	value++;
	len = str_len(value) - str_spn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[k++] = value[j];
	}
	new_value[k] = '\0';
	while (temp)
	{
		if (str_cmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		end_alias(&aliases, var_name, new_value);
}

/**
 * alias_print - Prints alias in the format name='value'.
 * @alias: Pointer to an alias.
 */
void alias_print(alias_t *alias)
{
	char *alias_string;
	int len = str_len(alias->name) + str_len(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	str_cpy(alias_string, alias->name);
	str_cat(alias_string, "='");
	str_cat(alias_string, alias->value);
	str_cat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}
/**
 * _aliases_ - replace matching aliaswith their value.
 * @args: pointer to the arguments.
 *
 * Return: pointer to the arguments.
 */
char **_aliases_(char **args)
{
	alias_t *temp;
	int i;
	char *new_value;

	if (str_cmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		while (temp)
		{
			if (str_cmp(args[i], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (str_len(temp->value) + 1));
				if (!new_value)
				{
					freeargs(args, args);
					return (NULL);
				}
				str_cpy(new_value, temp->value);
				free(args[i]);
				args[i] = new_value;
				i--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}
