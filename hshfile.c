#include "shell.h"
/**
 * hsh - main shell loop
 * @infostruct:a struct
 * @argv: vector
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *infostruct, char **argv)
{
	ssize_t cr = 0;
	int builtin_ret = 0;

	while (cr != -1 && builtin_ret != -2)
	{
		clrinfo(infostruct);
		if (interactive(infostruct))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		cr = gitinput(infostruct);
		if (cr != -1)
		{
			settinfo(infostruct, argv);
			builtin_ret = find_builtin(infostruct);
			if (builtin_ret == -1)
				find_cmd(infostruct);
		}
		else if (interactive(infostruct))
			_putchar('\n');
		freinfo(infostruct, 0);
	}
	create_hist(infostruct);
	freinfo(infostruct, 1);
	if (!interactive(infostruct) && infostruct->status)
		exit(infostruct->status);
	if (builtin_ret == -2)
	{
		if (infostruct->err_num == -1)
			exit(infostruct->status);
		exit(infostruct->err_num);
	}
	return (builtin_ret);
}



/**
 * find_builtin - finds a builtin command
 * @infostruct: a struct
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *infostruct)
{
	int countr, builtin_re = -1;
	builtin_table builtinarr[] = {
		{"exit", exshell},
		{"env", _myenvironment},
		{"help", hlp},
		{"history", myhist},
		{"setenv", _mysetenviron},
		{"unsetenv", _myunsetenv},
		{"cd", changdir},
		{"alias", alis},
		{NULL, NULL}
	};

	for (countr = 0; builtinarr[countr].type; countr++)
		if (_strcompar(infostruct > argv[0], builtinarr[countr].type) == 0)
		{
			infostruct->line_count++;
			builtin_re = builtinarr[countr].func(infostruct);
			break;
		}
	return (builtin_re);
}

/**
 * find_cmd - finds a command in PATH
 * @infostruct: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *infostruct)
{
	char *path = NULL;
	int countr1, countr2;

	infostruct->path = infostruct->argv[0];
	if (infostruct->linecount_flag == 1)
	{
		infostruct->line_count++;
		infostruct->linecount_flag = 0;
	}
	for (countr1 = 0, countr2 = 0;
			infostruct->arg[countr1]; i++)
		if (!is_delim(infostruct->arg[countr1], " \t\n"))
			countr2++;
	if (!countr2)
		return;

	path = find_path(infostruct, _getenvironment(infostruct, "PATH="),
	  infostruct->argv[0]);
	if (path)
	{
		infostruct->path = path;
		cmdfork(info);
	}
	else
	{
		if ((interactive(infostruct) ||	_getenvironment(infostruct, "PATH=")
			|| infostruct->argv[0][0] == '/') &&
			excut_cmd(infostruct, infostruct->argv[0]))
			cmdfork(infostruct);
		else if (*(infostruct->arg) != '\n')
		{
			infostruct->status = 127;
			print_error(infostruct, "not found\n");
		}
	}
}


/**
 * cmdfork- forks a a thread
 * @infostruct: a struct
 * Return: void
 */
void cmdfork(info_t *infostruct)
{
	pid_t chid;

	chid = fork();
	if (chid == -1)
	{
		perror("Error:");
		return;
	}
	if (chid == 0)
	{
		if (execve(infostruct->path, infostruct->argv, getEnvironment(infostruct))
				== -1)
	{
			freinfo(infostruct, 1);
		if (errno == EACCES)
			exit(126);
			exit(1);
	}
	}
	else
	{
		wait(&(infostruct->status));
		if (WIFEXITED(infostruct->status))
		{
			infostruct->status = WEXITSTATUS(infostruct->status);
			if (infostruct->status == 126)
				print_error(infostruct, "Permission denied\n");
		}
	}
}
