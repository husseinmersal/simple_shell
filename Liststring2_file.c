#include "shell.h"

/**
 * length_of_list- a function that determines the length of the list
 * @ptrh: pointer to first node
 *
 * Return: is the size of the list
 */
size_t length_of_list(const liststr_t *ptrh)
{
	size_t countr = 0;

	while (ptrh)
	{
		ptrh = ptrh->next;
		countr++;
	}
	return (countr);
}

/**
 * ltos- returns an array of strings of the list->str
 * @ptrh: a pointer that points to first node
 *
 * Return: is the array of the string that returns
 */
char **ltos(liststr_t *ptrh)
{
	liststr_t *node = ptrh;
	size_t countr = length_of_list(ptrh), countr2;
	char **strngs;
	char *strng;

	if (!ptrh || !countr)
		return (NULL);
	strngs = malloc(sizeof(char *) * (countr + 1));
	if (!strngs)
		return (NULL);
	for (countr = 0; node; node = node->next, countr++)
	{
		strng = malloc(_stringleng(node->strng) + 1);
		if (!strng)
		{
			for (countr2 = 0; countr2 < countr; countr2++)
				free(strngs[countr2]);
			free(strngs);
			return (NULL);
		}

		strng = _strngcopy(strng, node->strng);
		strngs[countr] = strng;
	}
	strngs[countr] = NULL;
	return (strngs);
}


/**
 * prent_lest - a function that prints all elements of a the list
 * @ptrh: is a pointer that points to the first node
 *
 * Return: size of list
 */
size_t prent_lest(const liststr_t *ptrh)
{
	size_t countr = 0;

	while (ptrh)
	{
		_puts(convnum(ptrh->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(ptrh->strng ? ptrh->strng : "(nil)");
		_puts("\n");
		ptrh = ptrh->next;
		countr++;
	}
	return (countr);
}

/**
 * ThenodeStartsWith- a functions returns a prfx
 * @pnode: pointer to list head
 * @prfx: a string that will be searched
 * @charac:  a string will be searched with
 * Return: match node or null
 */
liststr_t *ThenodeStartsWith(liststr_t *pnode, char *prfx, char charac)
{
	char *ptr = NULL;

	while (pnode)
	{
		ptr = starts_with_char(pnode->strng, prfx);
		if (ptr && ((charac == -1) || (*ptr == charac)))
			return (pnode);
		pnode = pnode->next;
	}
	return (NULL);
}

/**
 * get_index_of_node: this function will be return the index of the node
 * @ptrh: the pointer that points to the head
 * @nod: a pointer that pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_index_of_node(liststr_t *ptrh, liststr_t *nod)
{
	size_t countr = 0;

	while (ptrh)
	{
		if (ptrh == nod)
			return (countr);
		ptrh = ptrh->next;
		countr++;
	}
	return (-1);
}
