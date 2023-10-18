#include "shell.h"

/**
 * _errston - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string
 *       -1 on error
 */
int _errston(char *str)
{
	int countr = 0;
	unsigned long int reslt = 0;

	if (*str == '+')
		str++;
	for (countr = 0;  str[countr] != '\0'; countr++)
	{
		if (str[countr] >= '0' && str[countr] <= '9')
		{
			reslt *= 10;
			reslt += (str[countr] - '0');
			if (reslt  > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (reslt);
}

/**
 * print_error - a function that prints an error message
 * @infoobject: is an argument as an object from info_t struct
 * @errstrng: string contains an error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *infoobject, char *errstrng)
{
	_strputs(infoobject->fname);
	_strputs(": ");
	prntdec(infoobject->line_count, STDERR_FILENO);
	_strputs(": ");
	_strputs(infoobject->argv[0]);
	_strputs(": ");
	_strputs(errstrng);
}

/**
 * prntdec - convert a decimal number (integer) to number (base 10)
 * @inpt: the input data
 * @filedesk: the a file description will be written
 *
 * Return: number of characters printed
 */
int prntdec(int inpt, int filedesk)
{
	int (*__putchar)(char) = _putchar;
	int iterat, counter = 0;
	unsigned int _absol_, currvalu;

	if (filedesk == STDERR_FILENO)
		__putchar = _eputchar;
	if (inpt < 0)
	{
		_absol_ = -inpt;
		__putchar('-');
		counter++;
	}
	else
		_absol_ = inpt;
	currvalu = _absol_;
	for (iterat = 1000000000; iterat > 1; iterat /= 10)
	{
		if (_absol_  / iterat)
		{
			__putchar('0' + currvalu / iterat);
			counter++;
		}
		currvalu %= iterat;
	}
	__putchar('0' + currvalu);
	counter++;

	return (counter);
}

/**
 * convnum- converter function
 * @numb:is an input number
 * @bas: base
 * @flg: argument flag
 * Return: string
 */
char *convnum(long int numb, int bas, int flg)
{
	static char *strarr;
	static char buf[50];
	char signat = 0;
	char *ptr;
	unsigned long n = numb;

	if (!(flg & COV_UNSGND) && numb < 0)
	{
		n = -numb;
		signat = '-';

	}
	strarr = flg & COV_LCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buf[49];
	*ptr = '\0';

	do	{
		*--ptr = strarr[n % bas];
		n /= bas;
	} while (n != 0);

	if (signat)
		*--ptr = signat;
	return (ptr);
}

/**
 * remcom- function: r remove function
 * @buff: addres to string
 *
 * Return: Always 0;
 */
void remcom(char *buff)
{
	int countr;

	for (countr = 0; buff[countr] != '\0'; countr++)
		if (buff[countr] == '#' && (!countr || buff[countr - 1] == ' '))
		{
			buff[countr] = '\0';
			break;
		}
}
