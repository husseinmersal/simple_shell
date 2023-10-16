#include "shell.h"

/**
 * git_fil_hist - returns the history of the file
 * @infostruct: a struct
 *
 * Return: history
 */

char *git_fil_hist(info_t *infostruct)
{
	char *buff, *fol;

	fol = _getenvironment(infostruct, "HOME=");
	if (!fol)
		return (NULL);
	buff = malloc(sizeof(char) * (_stringleng(fol) + _stringleng(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strngcopi(buff, fol);
	_strngcopi(buff, "/");
	_strngcopi(buff, HIST_FILE);
	return (buff);
}


/**
 * create_hist- intiallize a file
 * @infostruct: a struct
 *
 * Return: 1 on success, else -1
 */
int create_hist(info_t *infostruct)
{
	ssize_t fdiscription;
	char *failname = git_fil_hist(infostruct);
	liststr_t *pnode = NULL;

	if (!failname)
		return (-1);

	fdiscription = open(failname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(failname);
	if (fdiscription == -1)
		return (-1);
	for (pnode = infostruct->history; pnode; pnode = pnode->next)
	{
		_putsfd(pnode->str, fdiscription);
		_putfildescriptor('\n', fdiscription);
	}
	_putfildescriptor(BUF_FLUSH, fdiscription);
	close(fdiscription);
	return (1);
}

/**
 * redhist- reads history from file
 * @infostruct: a struct
 *
 * Return: histcount on success, 0 otherwise
 */
int redhist(info_t *infostruct)
{
	int countr, last = 0, lincountr = 0;
	ssize_t fldisc, rdlen, filez = 0;
	struct stat st;
	char *buff = NULL, *filename = git_fil_hist(infostruct);

	if (!filename)
		return (0);

	fldisc = open(filename, O_RDONLY);
	free(filename);
	if (fldisc == -1)
		return (0);
	if (!fstat(fldisc, &st))
		filez = st.st_size;
	if (filez < 2)
		return (0);
	buff = malloc(sizeof(char) * (filez + 1));
	if (!buff)
		return (0);
	rdlen = read(fldisc, buff, filez);
	buff[filez] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fldisc);
	for (countr = 0; countr < filez; countr++)
		if (buff[countr] == '\n')
		{
			buff[countr] = 0;
			build_hist(infostruct, buff + last, lincountr++);
			last = countr + 1;
		}
	if (last != countr)
		build_hist(infostruct, buff + last, lincountr++);
	free(buff);
	infostruct->histcount = lincountr;
	while (infostruct->histcount-- >= HIST_MAX)
		delnod(&(infostruct->history), 0);
	renew_hist(infostruct);
	return (infostruct->histcount);
}



/**
 * build_hist - add new history
 * @infostruct: a struct
 * @buff: buffer
 * @lincont: line counter
 *
 * Return: Always 0
 */
int build_hist(info_t *infostruct, char *buff, int lincont)
{
	liststr_t *pnode = NULL;

	if (infostruct->history)
		pnode = infostruct->history;
	adnodend(&pnode, buff, lincont);

	if (!infostruct->history)
		infostruct->history = pnode;
	return (0);
}



/**
 * renew_hist - renew history
 * @infostruct:  a struct
 * Return: return the new history
 */
int renew_hist(info_t *infostruct)
{
	liststr_t *pnode = infostruct->history;
	int countr = 0;

	while (pnode)
	{
		pnode->numb = countr++;
		pnode = pnode->next;
	}
	return (infostruct->histcount = countr);
}

