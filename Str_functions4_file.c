#include "shell.h"

/**
 * **stringsplit - split a string into words. Repeat delimiter will be ignored
 * @strng: the input string
 * @deli: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **stringsplit(char *strng, char *deli)
{
	int countr1, countr2, countr3, countr4, numbcount = 0;
	char **newstr;

	if (strng == NULL || strng[0] == 0)
		return (NULL);
	if (!deli)
		deli = " ";
	for (countr1 = 0; strng[countr1] != '\0'; countr1++)
		if (!is_delim(strng[countr1], deli) && (is_delim(strng[countr1 + 1], deli)
					|| !strng[countr1 + 1]))
			numbcount++;

	if (numbcount == 0)
		return (NULL);
	newstr = malloc((1 + numbcount) * sizeof(char *));
	if (!newstr)
		return (NULL);
	for (countr1 = 0, countr2 = 0; countr2 < numbcount; countr2++)
	{
		while (is_delim(strng[countr1], deli))
			countr1++;
		countr3 = 0;
		while (!is_delim(strng[countr1 + countr3], deli)
			&& strng[countr1 + countr3])
			countr3++;
		newstr[countr2] = malloc((countr3 + 1) * sizeof(char));
		if (!newstr[countr2])
		{
			for (countr3 = 0; countr3 < countr2; countr3++)
				free(newstr[countr3]);
			free(newstr);
			return (NULL);
		}
		for (countr4 = 0; countr4 < countr3; countr4++)
			newstr[countr2][countr4] = strng[countr1++];
		newstr[countr2][countr4] = 0;
	}
	newstr[countr2] = NULL;
	return (newstr);
}

/**
 * **stringsplit2 - splits a string into words
 * @strng: the input string
 * @deli: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **stringsplit2(char *strng, char deli)
{
	int countr1, countr2, countr3, countr4, numbcount = 0;
	char **newstr;

	if (strng == NULL || strng[0] == 0)
		return (NULL);
	for (countr1 = 0; strng[countr1] != '\0'; countr1++)
		if ((strng[countr1] != deli && strng[countr1 + 1] == deli) ||
		    (strng[countr1] != deli && !strng[countr1 + 1])
			|| strng[countr1 + 1] == deli)
			numbcount++;
	if (numbcount == 0)
		return (NULL);
	newstr = malloc((1 + numbcount) * sizeof(char *));
	if (!newstr)
		return (NULL);
	for (countr1 = 0, countr2 = 0; countr2 < numbcount; countr2++)
	{
		while (strng[countr1] == deli && strng[countr1] != deli)
			countr1++;
		countr3 = 0;
		while (strng[countr1 + countr3] != deli && strng[countr1 + countr3]
				&& strng[countr1 + countr3] != deli)
			countr3++;
		newstr[countr2] = malloc((countr3 + 1) * sizeof(char));
		if (!newstr[countr2])
		{
			for (countr3 = 0; countr3 < countr2; countr3++)
				free(newstr[countr3]);
			free(newstr);
			return (NULL);
		}
		for (countr4 = 0; countr4 < countr3; countr4++)
			newstr[countr2][countr4] = strng[countr1++];
		newstr[countr2][countr4] = 0;
	}
	newstr[countr2] = NULL;
	return (newstr);
}
