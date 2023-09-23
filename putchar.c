#include "main.h"

/**
 * str_cat - Concantenates two strings.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 *
 * Return: Pointer to destination string.
 */
char *str_cat(char *dest, const char *src)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp =  src;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}

/**
 * str_cpy - Copies the string pointed to by src, including the
 *           terminating null byte, to the buffer pointed by des.
 * @dest: Pointer to the destination of copied string.
 * @src: Pointer to the src of the source string.
 *
 * Return: Pointer to dest.
 */
char *str_cpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * strn_cat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * @num: number of bytes to copy from src.
 *
 * Return: Pointer to destination string.
 */
char *strn_cat(char *dest, const char *src, size_t num)
{
	size_t dest_len = str_len(dest);
	size_t i;

	for (i = 0; i < num && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return (dest);
}

/**
 * str_len - Returns the length of a string.
 * @s:  string.
 *
 * Return: The length of the character string.
 */
int str_len(const char *s)
{
	int lent = 0;

	if (!s)
		return (lent);
	for (lent = 0; s[lent]; lent++)
		;
	return (lent);
}

/**
 * str_chr - Locates a character in a string.
 * @s: The string to be searched.
 * @c: The character to be located.
 *
 * Return: If c is found, a pointer to the first occurence.
 *         otherwise NULL.
 */
char *str_chr(char *s, char c)
{
	int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] == c)
			return (s + i);
	}

	return (NULL);
}
