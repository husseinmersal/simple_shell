#include "shell.h"

/**
 * myhist- display hitory.
 * @infostruct: a struct
 *  Return: Always 0
 */
int myhist(info_t *infostruct)
{
	prent_lest(infostruct->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @infostruct: a struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *infostruct, char *str)
{
	char *ptr, charac;
	int real;

	ptr = _strngcharct(str, '=');
	if (!ptr)
		return (1);
	charac = *ptr;
	*ptr = 0;
	real = delnod(&(infostruct->alias),
		get_index_of_node(infostruct->alias, ThenodeStartsWith(infostruct->alias,
			str, -1)));
	*ptr = charac;
	return (real);
}

/**
 * set_alias - sets alias to string
 * @infostruct: a struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *infostruct, char *str)
{
	char *ptr;

	ptr = _strngcharct(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(infostruct, str));

	unset_alias(infostruct, str);
	return (adnodend(&(infostruct->alias), str, 0) == NULL);
}




















/**
 * print_alias - prints an alias string
 * @pnode: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(liststr_t  *pnode)
{
	char *ptr = NULL, *count = NULL;

	if (pnode)
	{
		ptr = _strngcharct(pnode->strng, '=');
		for (count = pnode->strng; count <= ptr; count++)
			_putchar(*count);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * alis- man alias
 * @infostruct: a struct
 *  Return: Always 0
 */
int alis(info_t *infostruct)
{
	int countr = 0;
	char *ptr = NULL;
	liststr_t *pnode = NULL;

	if (infostruct->argc == 1)
	{
		pnode = infostruct->alias;
		while (pnode)
		{
			print_alias(pnode);
			pnode = pnode->next;
		}
		return (0);
	}
	for (countr = 1; infostruct->argv[countr]; countr++)
	{
		ptr = _strngcharct(pnode->argv[countr], '=');
		if (ptr)
			set_alias(pnode, pnode->argv[countr]);
		else
			print_alias(ThenodeStartsWith(pnode->alias, pnode->argv[countr], '='));
	}

	return (0);
}

