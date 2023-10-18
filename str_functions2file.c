#include "shell.h"

/**
 * _strngcopy - copy a string
 * @destinat:is the destination
 * @srce: is the the source
 *
 * Return: pointer to destination
 */
char *_strngcopy(char *destinat, char *srce)
{
	int countr = 0;

	if (destinat == srce || srce == 0)
		return (destinat);
	while (srce[countr])
	{
		destinat[countr] = srce[countr];
		countr++;
	}
	destinat[countr] = 0;
	return (destinat);
}

/**
 * _strngduplic- this functions duplicates the string that passes to
 * @ptrstr: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strngduplic(const char *ptrstr)
{
	int length = 0;
	char *dupl;

	if (ptrstr == NULL)
		return (NULL);
	while (*ptrstr++)
		length++;
	dupl = malloc(sizeof(char) * (length + 1));
	if (!dupl)
		return (NULL);
	for (length++; length--;)
		dupl[length] = *--ptrstr;
	return (dupl);
}

/**
 *_puts - prints an srgumant
 *@ptrstr: a string
 *@countr: countrs the length
 * Return: Nothing
 */
void _puts(char *ptrstr)
{
	int countr = 0;

	if (!ptrstr)

		return;
	while (ptrstr[countr] != '\0')
	{
		_putchar(ptrstr[countr]);
		countr++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int countr;
	static char bufer[W_BUFF_SIZE];

	if (c == BUFF_FLCH || countr >= W_BUFF_SIZE)
	{
		write(1, bufer, countr);
		countr = 0;
	}
	if (c != BUFF_FLCH)
		bufer[countr++] = c;
	return (1);
}
