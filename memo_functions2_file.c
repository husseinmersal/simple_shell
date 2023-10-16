#include "shell.h"

/**
 * pointfree- a function that frees the pointers and make the address null
 * @pptr: address of the pointer to be free
 *
 * Return: 1 if freed, otherwise 0.
 */
int pointfree(void **pptr)
{
	if (pptr && *pptr)
	{
		free(*pptr);
		*pptr = NULL;
		return (1);
	}
	return (0);
}
