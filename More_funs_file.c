#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - is the function that checks if character is a delimeter
 * @charac: the char to be checked by the user
 * @deli: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char charac, char *deli)
{
	while (*deli)
		if (*deli++ == charac)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@charac: The character that will entered
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int charac)
{
	if ((charac >= 'a' && charac <= 'z') || (charac >= 'A' && charac <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_ston - converts a string to an integer
 *@str: is the string will be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _ston(char *str)
{
	int countr, signatr = 1, flag = 0, output;
	unsigned int reslt = 0;

	for (countr = 0;  str[countr] != '\0' && flag != 2; countr++)
	{
		if (str[countr] == '-')
			signatr *= -1;

		if (str[countr] >= '0' && str[countr] <= '9')
		{
			flag = 1;
			reslt *= 10;
			reslt += (str[countr] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (signatr == -1)
		output = -reslt;
	else
		output = reslt;

	return (output);
}

