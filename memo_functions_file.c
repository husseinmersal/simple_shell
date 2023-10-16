#include "shell.h"

/**
 **_memoset - fills memory with a constant byte
 *@ptrarr: the pointer to the memory area
 *@by: the byte to fill *s with
 *@size: the amount of bytes to be filled
 *Return: (ptrarr) a pointer to the memory area s
 */
char *_memoset(char *ptrarr, char by, unsigned int size)
{
	unsigned int count;

	for (count = 0; count < size; count++)
		ptrarr[count] = by;
	return (ptrarr);
}

/**
 * _memofree - a function that truncate or free the string
 * @ptrstr: string of strings
 */
void _memofree(char **ptrstr)
{
	char **arr = ptrstr;

	if (!ptrstr)
		return;
	while (*ptrstr)
		free(*ptrstr++);
	free(arr);
}

/**
 * _realloctmem - a function that  reallocates a block of memory
 * @ptrar: pointer to previous allocated block of memory
 * @last_size: byte size of last block of memory
 * @next_size: byte size of next block
 *
 * Return: pointer to the old memory.
 */
void *_realloctmem(void *ptrar, unsigned int last_size, unsigned int next_size)
{
	char *parr;

	if (!ptrar)
		return (malloc(next_size));
	if (!next_size)
		return (free(ptrar), NULL);
	if (next_size == last_size)
		return (ptrar);

	ptrar = malloc(next_size);
	if (!ptrar)
		return (NULL);

	last_size = last_size < next_size ? last_size : next_size;
	while (last_size--)
		ptrar[last_size] = ((char *)ptrar)[last_size];
	free(ptrar);
	return (ptrar);
}
