#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @infostruct: parameter struct
 * @buff: a buffer
 * @lngth: address of length
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *infostruct, char **buff, size_t *lngth)
{
	ssize_t read = 0;
	size_t len_p = 0;

	if (!*lngth)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		read = getline(buff, &len_p, stdin);
#else
		read = _getline(infostruct, buff, &len_p);
#endif
		if (read > 0)
		{
			if ((*buff)[read - 1] == '\n')
			{
				(*buff)[read - 1] = '\0';
				read--;
			}
			infostruct->linecount_flag = 1;
			remcom(*buff);
			build_hist(infostruct, *buff, infostruct->histcount++);
			{
				*lngth = read;
				infostruct->cmd_buf = buff;
			}
		}
	}
	return (read);
}










/**
 * gitinput- gets aline
 * @infostruct:a struct
 *
 * Return: bytes read
 */
ssize_t gitinput(info_t *infostruct)
{
	static char *buff;
	static size_t countr, countr2, lngth;
	ssize_t read = 0;
	char **bufptr = &(infostruct->arg), *ptr;

	_putchar(BUFF_FLCH);
	read = input_buf(infostruct, &buff, &lngth);
	if (read == -1)
		return (-1);
	if (lngth)
	{
		countr2 = countr;
		ptr = buff + countr;

		ckchain(infostruct, buff, &countr2, countr, lngth);
		while (countr2 < lngth)
		{
			if (mychain(infostruct, buff, &countr2))
				break;
			countr2++;
		}

		countr = countr2 + 1;
		if (countr >= lngth)
		{
			countr = lngth = 0;
			infostruct->cmd_buf_type = CMD_NORM;
		}

		*bufptr = ptr;
		return (_stringleng(ptr));
	}

	*bufptr = buff;
	return (read);
}

/**
 * readbuffer- reads a buffer
 * @infostruct: a struct
 * @buff: buffer
 * @siz: size
 *
 * Return: read
 */
ssize_t readbuffer(info_t *infostruct, char *buff, size_t *siz)
{
	ssize_t re = 0;

	if (*siz)
		return (0);
	re = read(infostruct->readfd, buff, R_BUFF_SIZE);
	if (re >= 0)
		*siz = re;
	return (re);
}

/**
 * _getline - gets line
 * @infostruct: a struct
 * @ptr: a pointer to buffer
 * @lngth: size of buffer
 *
 * Return: s
 */
int _getline(info_t *infostruct, char **ptr, size_t *lngth)
{
	static char buff[R_BUFF_SIZE];
	static size_t countr, leng;
	size_t sizek;
	ssize_t read = 0, sizes = 0;
	char *pch = NULL, *new_p = NULL, *charac;

	pch = *ptr;
	if (pch && lngth)
		sizes = *lngth;
	if (countr == leng)
		countr = leng = 0;

	read = readbuffer(infostruct, buff, &leng);
	if (read == -1 || (read == 0 && leng == 0))
		return (-1);

	charac = _strngcharct(buff + countr, '\n');
	sizek = charac ? 1 + (unsigned int)(charac - buff) : leng;
	new_p = _realloctmem(pch, sizes, sizes ? sizes + sizek : sizek + 1);
	if (!new_p)
		return (pch ? free(pch), -1 : -1);

	if (sizes)
		_strngconcat(new_p, buff + countr, sizek - countr);
	else
		_strngcopi(new_p, buff + countr, sizek - countr + 1);

	sizes += sizek - countr;
	countr = sizek;
	pch = new_p;

	if (lngth)
		*lngth = sizes;
	*ptr = pch;
	return (sizes);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFF_FLCH);
}

