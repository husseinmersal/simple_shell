#include "shell.h"

/**
 * exshell- exits our shell
 * @infostruct : a struct
 *  Return: exits with  a status
 */
int exshell(info_t *infostruct)
{
	int excheck;

	if (infostruct->argv[1])
	{
		excheck = _errston(infostruct->argv[1]);
		if (excheck == -1)
		{
			infostruct->status = 2;
			print_error(infostruct, "Illegal number: ");
			_strputs(infostruct->argv[1]);
			_eputchar('\n');
			return (1);
		}
		infostruct->err_num = _errston(infostruct->argv[1]);
		return (-2);
	}
	infostruct->err_num = -1;
	return (-2);
}








/**
 * changdir- change directory
 * @infostruct: a struct.
 *  Return: Always 0
 */
int changdir(info_t *infostruct)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!infostruct->argv[1])
	{
		dir = _getenvironment(infostruct, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenvironment(infostruct, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcompar(infostruct->argv[1], "-") == 0)
	{
		if (!_getenvironment(infostruct, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenvironment(infostruct, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenvironment(infostruct, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(infostruct->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(infostruct, "can't cd to ");
		_strputs(infostruct->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenvironment(infostruct, "OLDPWD", _getenvironment(infostruct, "PWD="));
		_setenvironment(infostruct, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}



/**
 * hlp- changes directory
 * @infostruct: a struct
 *  Return: Always 0
 */
int hlp(info_t *infostruct)
{
	char **arg_arr;

	arg_arr = infostruct->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr); /* temp att_unused workaround */
	return (0);
}

