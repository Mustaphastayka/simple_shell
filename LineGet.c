#include "shell.h"
/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @lenvar: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(t__info *info, char **buffer, size_t *lenvar)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*lenvar)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, CtrCBlock);
#if USE_GETLINE
		r = getline(buffer, &len_p, stdin);
#else
		r = LineGet(info, buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}
			info->countlifeflags = 1;
			CommRemover(*buffer);
			HistoryListBuild(info, *buffer, info->counthists++);
			{
				*lenvar = r;
				info->cmd_buf = buffer;
			}
		}
	}
	return (r);
}
/**
 * LineInputGet - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t LineInputGet(t__info *info)
{
	static char *buffer;
	static size_t i, j, lenvar;
	ssize_t r = 0;
	char **buf_p = &(info->strarg), *p;

	WrCharPutC(BUF_FLUSH);
	r = input_buf(info, &buffer, &lenvar);
	if (r == -1)
		return (-1);
	if (lenvar)
	{
		j = i;
		p = buffer + i;

		ChainCheck(info, buffer, &j, i, lenvar);
		while (j < lenvar)
		{
			if (Chains(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= lenvar)
		{
			i = lenvar = 0;
			info->BufCmdType = CMD_NORM;
		}

		*buf_p = p;
		return (RetuStrlen(p));
	}

	*buf_p = buffer;
	return (r);
}
/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(t__info *info, char *buffer, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->FdReadinp, buffer, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}
/**
 * LineGet - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptbfr: address of pointer to buffer, preallocated or NULL
 * @lengptr: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int LineGet(t__info *info, char **ptbfr, size_t *lengptr)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptbfr;
	if (p && lengptr)
		s = *lengptr;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = FoundCharInString(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = RealloBlMem(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		Con2String(new_p, buffer + i, k - i);
	else
		CopyString(new_p, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (lengptr)
		*lengptr = s;
	*ptbfr = p;
	return (s);
}
/**
 * CtrCBlock - blocks ctrl-C
 * @number_sign: the signal number
 *
 * Return: void
 */
void CtrCBlock(__attribute__((unused)) int number_sign)
{
	InpStrPrint("\n");
	InpStrPrint("$ ");
	WrCharPutC(BUF_FLUSH);
}
