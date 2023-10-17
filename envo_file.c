#include "shell.h"

/**
 * _myenvironment- returns environment
 * @infostruct: a struct
 * Return: Always 0
 */
int _myenvironment(info_t *infostruct)
{
	prntlststring(infostruct->env);
	return (0);
}

/**
 * _getenvironment- gets the value of the environment
 * @infostruct: Structure containing potential arguments. Used to maintain
 * @pname: env var name
 *
 * Return: the value
 */
char *_getenvironment(info_t *infostruct, const char *pname)
{
	liststr_t *pnode = infostruct->env;
	char *ptr;

	while (pnode)
	{
		ptr = starts_with_char(pnode->strng, pname);
		if (ptr && *ptr)
			return (ptr);
		pnode = pnode->next;
	}
	return (NULL);
}




/**
 * _mysetenviron - intiliazie a env
 * @infostruct: a struct
 *  Return: Always 0
 */
int _mysetenviron(info_t *infostruct)
{
	if (infostruct->argc != 3)
	{
		_strputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenvironment(infostruct, infostruct->argv[1], infostruct->argv[2]))
		return (0);
	return (1);
}


/**
 * _myunsetenv - Remove the env var
 * @infostruct:  a struct
 *  Return: Always 0
 */
int _myunsetenv(info_t *infostruct)
{
	int countr;

	if (infostruct->argc == 1)
	{
		_strputs("Too few arguements.\n");
		return (1);
	}
	for (countr = 1; countr <= infostruct->argc; countr++)
		_setenvironment(infostruct, infostruct->argv[countr]);

	return (0);
}



/**
 * populate_envo - populates the environment
 * @infostruct: a struct
 * Return: Always 0
 */
int populate_envo(info_t *infostruct)
{
	liststr_t *pnode = NULL;
	size_t countr;

	for (countr = 0; environ[countr]; countr++)
		adnodend(&pnode, environ[countr], 0);
	infostruct->env = pnode;
	return (0);
}

