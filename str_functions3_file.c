#include "shell.h"

/**
 **_strngcopi - copies a string
 *@destinat: the destination string that copied
 *@srce: the source string
 *@numb: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strngcopi(char *destinat, char *srce, int numb)
{
	int count1, count2;
	char *s = destinat;

	count1 = 0;
	while (srce[count1] != '\0' && count1 < numb - 1)
	{
		destinat[count1] = srce[count1];
		count1++;
	}
	if (count1 < numb)
	{
		count2 = count1;
		while (count2 < numb)
		{
			destinat[count2] = '\0';
			count2++;
		}
	}
	return (s);
}

/**
 **_strngconcat - concatenates two strings
 *@destinat: the first string that pases
 *@srce: the second string that pases
 *@numb: the number of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strngconcat(char *destinat, char *srce, int numb)
{
	int count1, count2;
	char *s = destinat;

	count1 = 0;
	count2 = 0;
	while (destinat[count1] != '\0')
		count1++;
	while (srce[count2] != '\0' && count2 < numb)
	{
		destinat[count1] = srce[count2];
		count1++;
		count2++;
	}
	if (count2 < numb)
		destinat[count1] = '\0';
	return (s);
}

/**
 **_strngcharct - locates a character in a string
 *@ptrstr: the string to be parsed
 *@charac: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strngcharct(char *ptrstr, char charac)
{
	do {
		if (*ptrstr == charac)
			return (ptrstr);
	} while (*ptrstr++ != '\0');

	return (NULL);
}
