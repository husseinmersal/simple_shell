#include "shell.h"

/**
 * clrinfo- clear a struct
 * @infostruct:a struct
 */
void clrinfo(info_t *infostruct)
{
	infostruct->arg = NULL;
	infostruct->argv = NULL;
	infostruct->path = NULL;
	infostruct->argc = 0;
}

/**
 * settinfo- info  as struct
 * @infostruct: struct address
 * @argvector: argument vector
 */
void settinfo(info_t *infostruct, char **argvector)
{
	int countr = 0;

	infostruct->fname = argvector[0];
	if (infostruct->arg)
	{
		infostruct->argv = stringsplit(infostruct->arg, " \t");
		if (!infostruct->argv)
		{
			infostruct->argv = malloc(sizeof(char *) * 2);
			if (infostruct->argv)
			{
				info->argv[0] = _strngduplic(infostruct->arg);
				info->argv[1] = NULL;
			}
		}
		for (countr = 0; infostruct->argv && infostruct->argv[countr]; countr++)
			;
		infostruct->argc = countr;

		repalias(infostruct);
		repvars(infostruct);
	}
}

/**
 * freinfo- truncate the struct
 * @infostruct: struct
 * @all: true if freeing all fields
 */
void freinfo(info_t *infostruct, int all)
{
	_memofree(infostruct->argv);
	infostruct->argv = NULL;
	infostruct->path = NULL;
	if (all)
	{
		if (!infostruct->cmd_buf)
			free(infostruct->arg);
		if (infostruct->env)
			frlst(&(infostruct->env));
		if (infostruct->history)
			frlst(&(infostruct->history));
		if (infostruct->alias)
			frlst(&(infostruct->alias));
		_memofree(infostruct->environ);
			infostruct->environ = NULL;
		pointfree((void **)infostruct->cmd_buf);
		if (infostruct->readfd > 2)
			close(infostruct->readfd);
		_putchar(BUF_FLUSH);
	}
}
