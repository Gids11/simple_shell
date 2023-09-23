#include "main.h"

/**
 * str_cmp - Compares two strings.
 * @s1: first string to be compared.
 * @s2: second string to be compared.
 *
 * Return: Positive byte difference if s1 > s2
 *         0 if s1 = s2
 *         Negative byte difference if s1 < s2
 */
int str_cmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * str_spn - Gets the length of a prefix substring.
 * @s: string to be searched.
 * @a: prefix to be measured.
 *
 * Return: The number of bytes in s which
 *         consist only of bytes from accept.
 */
int str_spn(char *s, char *a)
{
	int bytes = 0;
	int index;

	while (*s)
	{
		for (index = 0; a[index]; index++)
		{
			if (*s == a[index])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}

/**
 * strn_cmp - Compare two strings.
 * @s1: string.
 * @s2: string.
 * @num: bytes of the strings to compare.
 *
 * Return: Less than 0 if s1 is shorter than s2.
 *         0 if s1 and s2 match.
 *         Greater than 0 if s1 is longer than s2.
 */
int strn_cmp(const char *s1, const char *s2, size_t num)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < num; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == num)
		return (0);
	else
		return (-15);
}
