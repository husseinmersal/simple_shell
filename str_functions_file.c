#include "shell.h"

/**
 * _stringleng - returns a length of a string
 * @st: the string whose length to check
 *
 * Return: integer length of the string
 */
int _stringleng(char *st)
{
	int countr = 0;

	if (!st)
		return (0);

	while (*st++)
		countr++;
	return (countr);
}

/**
 * _strcompar - performs comparing
 * @st1: the first string variable
 * @st2: the second string variable
 *
 * Return: negative if st1 < st2, positive if st1 > st2, zero if st1 == st2
 */
int _strcompar(char *st1, char *st2)
{
	while (*st1 && *st2)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
	}
	if (*st1 == *st2)
		return (0);
	else
		return (*st1 < *st2 ? -1 : 1);
}

/**
 * starts_with_char - checks if needle starts with hellostack
 * @hellostack: a string to be searched
 * @needle: the substring to find
 *
 * Return: address of next char of hellostack or NULL
 */
char *starts_with_char(const char *hellostack, const char *needle)
{
	while (*needle)
		if (*needle++ != *hellostack++)
			return (NULL);
	return ((char *)hellostack);
}

/**
 * _stringconcat - concatenates the two string variables
 * @destinat: the destinat buffer
 * @srce: the source buffer
 *
 * Return: pointer to destinat buffer
 */
char *_stringconcat(char *destinat, char *srce)
{
	char *concat = destinat;

	while (*destinat)
		destinat++;
	while (*srce)
		*destinat++ = *srce++;
	*destinat = *srce;
	return (concat);
}
