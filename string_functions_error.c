#include "shell.h"

/**
 *_strputs - a function that prints the string’s inputs
 * @strng: the string that will be printed
 * Return: void function
 */
void _strputs(char *strng)
{
	int countr = 0;

	if (!strng)
		return;
	while (strng[countr] != '\0')
	{
		_eputchar(strng[countr]);
		countr++;
	}
}

/**
 * _eputchar - writes  a char to stderr
 * @charac: a char that prints
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char charac)
{
	static int countr;
	static char buffe[W_BUFF_SIZE];

	if (charac == BUFF_FLCH || countr >= W_BUFF_SIZE)
	{
		write(2, buffe, countr);
		countr = 0;
	}
	if (charac != BUF_FLUSH)
		buffe[countr++] = charac;
	return (1);
}



/**
 * _putfildescriptor- writes the character c to given fd
 * @charac: The character to print
 * @fildescript: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfildescriptor(char charac, int fildescript)
{
	static int countr;
	static char buff[W_BUFF_SIZE];

	if (charac == BUFF_FLCH || countr >= W_BUFF_SIZE)
	{
		write(fildescript, buff, countr);
		countr = 0;
	}
	if (charac != BUF_FLUSH)
		buff[countr++] = charac;
	return (1);
}

/**
 *_putsfd - a fun to prints a string input
 * @strng: a string printed
 * @filedescript: a filedescriptor
 *
 * Return: num of chars put
 */
int _putsfd(char *strng, int filedescript)
{
	int countr = 0;

	if (!strng)
		return (0);
	while (*strng)
	{
		countr += _putfildescriptor(*strng++, filedescript);
	}
	return (countr);
}

