#include "shell.h"

/**
 * getEnvironment- return a copy
 * @infostruct: a struct
 * Return: Always 0
 */
char **getEnvironment(info_t *infostruct)
{
	if (!infostruct->environ || infostruct->env_changed)
	{
		infostruct->environ = ltos(infostruct->env);
		infostruct->env_changed = 0;
	}

	return (infostruct->environ);
}

/**
 * _unsetenvironment- Remove the env var
 * @infostruct: a struct
 *  Return: 1 on delete, 0 otherwise
 * @var:string var
 */
int _unsetenvironment(info_t *infostruct, char *var)
{
	liststr_t *pnode = infostruct->env;
	size_t countr = 0;
	char *ptr;

	if (!pnode || !var)
		return (0);

	while (pnode)
	{
		ptr = starts_with_char(pnode->strng, var);
		if (ptr && *ptr == '=')
		{
			infostruct->env_changed = delnod(&(infostruct->env), countr);
			countr = 0;
			pnode = infostruct->env;
			continue;
		}
		pnode = pnode->next;
		countr++;
	}
	return (infostruct->env_changed);
}



/**
 * _setenvironment - Initialize an env var
 * @infostruct: a struct
 * @var: env variable
 * @val: string value
 *  Return: Always 0
 */
int _setenvironment(info_t *infostruct, char *var, char *val)
{
	char *buff = NULL;
	liststr_t *pnode;
	char *ptr;

	if (!var || !val)
		return (0);

	buff = malloc(_stringleng(var) + _stringleng(val) + 2);
	if (!buff)
		return (1);
	_strngcopy(buff, var);
	_stringconcat(buff, "=");
	_stringconcat(buff, val);
	pnode = infostruct->env;
	while (pnode)
	{
		ptr = starts_with_char(pnode->strng, var);
		if (ptr && *ptr == '=')
		{
			free(pnode->strng);
			pnode->strng = buff;
			infostruct->env_changed = 1;
			return (0);
		}
		pnode = pnode->next;
	}
	adnodend(&(infostruct->env), buff, 0);
	free(buff);
	infostruct->env_changed = 1;
	return (0);
}
