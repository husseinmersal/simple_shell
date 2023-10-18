#include "shell.h"

/**
 * excut_cmd - checks if is executable command
 * @infostruct: is a struct
 * @pt: the path of file
 *
 * Return: 1 if true, 0 otherwise
 */
int excut_cmd(info_t *infostruct, char *pt)
{
	struct stat sta;

	(void)infostruct;
	if (!pt || stat(pt, &sta))
		return (0);

	if (sta.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplchar- duplicates characters
 * @pstrng: the PATH string
 * @strt: starting index
 * @stp: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplchar(char *pstrng, int strt, int stp)
{
	static char buff[1024];
	int countr = 0, countr2 = 0;

	for (countr2 = 0, countr = strt; countr < stp; countr++)
		if (pstrng[countr] != ':')
			buff[countr2++] = pstrng[countr];
	buff[countr2] = 0;
	return (buff);
}

/**
 * find_path - findsthe path
 * @infostruct: the struct
 * @pstrng: the PATH string
 * @cmd: the cmd
  * Return: full path OR NULL
 */
char *find_path(info_t *infostruct, char *pstrng, char *cmd)
{
	int countr = 0, curpos = 0;
	char *path;

	if (!pstrng)
		return (NULL);
	if ((_stringleng(cmd) > 2) && starts_with_char(cmd, "./"))
	{
		if (excut_cmd(infostruct, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pstrng[countr] || pstrng[countr] == ':')
		{
			path = duplchar(pstrng, curpos, countr);
			if (!*path)
				_stringconcat(path, cmd);
			else
			{
				_stringconcat(path, "/");
				_stringconcat(path, cmd);
			}
			if (excut_cmd(infostruct, path))
				return (path);
			if (!pstrng[countr])
				break;
			curpos = countr;
		}
		countr++;
	}
	return (NULL);
}

