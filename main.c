#include "shell.h"

/**
 * main - s star function for the project
 * @argmntv: argum vector
 * @argmntc: argum count
 * Return: 0 on success, 1 on error
 */

int main(int argmntc, char **argmntv)
{
	info_t infostruct[] = { INFO_INIT };
	int fildescript = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fildescript)
		: "r" (fildescript));

	if (argmntc == 2)
	{
		fildescript = open(argmntv[1], O_RDONLY);
		if (fildescript == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_strputs(argmntv[0]);
				_strputs(": 0: Can't open ");
				_strputs(argmntv[1]);
				_eputchar('\n');
				_eputchar(BUFF_FLCH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		infostruct->readfd = fildescript;
	}
	populate_envo(infostruct);
	redhist(infostruct);
	hsh(infostruct, argmntv);
	return (EXIT_SUCCESS);
}

