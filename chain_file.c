#include "shell.h"

/**
 * mychain- checks if buffer is chain deli
 * @infostruct: a struct
 * @buff: buffer
 * @ptr: address of current position
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int mychain(info_t *infostruct, char *buff, size_t *ptr)
{
	size_t countr = *ptr;

	if (buff[countr] == '|' && buff[countr + 1] == '|')
	{
		buff[countr] = 0;
		countr++;
		infostruct->cmd_buf_type = CMD_OR;
	}
	else if (buff[countr] == '&' && buff[countr + 1] == '&')
	{
		buff[countr] = 0;
		countr++;
		infostruct->cmd_buf_type = CMD_AND;
	}
	else if (buff[countr] == ';')
	{
		buff[countr] = 0;
		infostruct->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = countr;
	return (1);
}

/**
 * ckchain- checks chaining
 * @infostruct: the parameter struct
 * @buff: the char buffer
 * @ptr: address of current position in buf
 * @countr: starting position in buf
 * @lngth: length of buf
 *
 * Return: Void
 */
void ckchain(info_t *infostruct, char *buff,
		size_t *ptr, size_t countr, size_t lngth)
{
	size_t countr2 = *ptr;

	if (infostruct->cmd_buf_type == CMD_AND)
	{
		if (infostruct->status)
		{
			buff[countr] = 0;
			countr2 = lngth;
		}
	}
	if (infostruct->cmd_buf_type == CMD_OR)
	{
		if (!infostruct->status)
		{
			buff[countr] = 0;
			countr2 = lngth;
		}
	}

	*ptr = countr2;
}








/**
 * repalias- replaces an aliases
 * @infostruct: a struct
 * Return: 1 if replaced, 0 otherwise
 */
int repalias(info_t *infostruct)
{
	int countr;
	liststr_t *pnode;
	char *ptr;

	for (countr = 0; countr < 10; countr++)
	{
		pnode = ThenodeStartsWith(infostruct->alias, infostruct->argv[0], '=');
		if (!pnode)
			return (0);
		free(infostruct->argv[0]);
		ptr = _strngcharct(pnode->strng, '=');
		if (!ptr)
			return (0);
		ptr = _strngduplic(ptr + 1);
		if (!ptr)
			return (0);
		infostruct->argv[0] = ptr;
	}
	return (1);
}

/**
 * repvars - replaces variables
 * @infostruct:a struct
 * Return: 1 if replaced, 0 otherwise
 */
int repvars(info_t *infostruct)
{
	int countr = 0;
	iiststr_t *pnode;

	for (countr = 0; infostruct->argv[countr]; countr++)
	{
		if (infostruct->argv[countr][0] != '$' || !infostruct->argv[countr][1])
			continue;

		if (!_strcompar(infostruct->argv[countr], "$?"))
		{
			repstring(&(infostruct->argv[countr]),
				_strngduplic(convnum(infostruct->status, 10, 0)));
			continue;
		}
		if (!_strcompar(infostruct->argv[countr], "$$"))
		{
			repstring(&(infostruct->argv[countr]),
				_strngduplic(convnum(getpid(), 10, 0)));
			continue;
		}
		pnode = ThenodeStartsWith(infostruct->env, &infostruct->argv[countr][1],
				'=');
		if (pnode)
		{
			repstring(&(infostruct->argv[countr]),
				_strngduplic(_strngcharct(pnode->str, '=') + 1));
			continue;
		}
		repstring(&infostruct->argv[countr], _strngduplic(""));

	}
	return (0);
}











/**
 * repstring- replaces string
 * @pre: address of string
 * @next: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int repstring(char **pre, char *next)
{
	free(*pre);
	*pre = next;
	return (1);
}

