#include "shell.h"
/**
 * FileHistory - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */
char *FileHistory(t__info *info)
{
	char *buffer, *dek;

	dek = EnvironGet(info, "HOME=");
	if (!dek)
		return (NULL);
	buffer = malloc(sizeof(char) * (RetuStrlen(dek) + RetuStrlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	CpString(buffer, dek);
	StringConc(buffer, "/");
	StringConc(buffer, HIST_FILE);
	return (buffer);
}
/**
 * TipeHistory - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int TipeHistory(t__info *info)
{
	ssize_t fd;
	char *Namefile = FileHistory(info);
	t__liste *node = NULL;

	if (!Namefile)
		return (-1);

	fd = open(Namefile, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(Namefile);
	if (fd == -1)
		return (-1);
	for (node = info->Histor; node; node = node->next_node)
	{
		StrPrint(node->str, fd);
		WrCharCtoFD('\n', fd);
	}
	WrCharCtoFD(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
 * HistoryRead - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int HistoryRead(t__info *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, drlen, filesize = 0;
	struct stat st;
	char *buffer = NULL, *filename = FileHistory(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		filesize = st.st_size;
	if (filesize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (filesize + 1));
	if (!buffer)
		return (0);
	drlen = read(fd, buffer, filesize);
	buffer[filesize] = 0;
	if (drlen <= 0)
		return (free(buffer), 0);
	close(fd);
	for (i = 0; i < filesize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			HistoryListBuild(info, buffer + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		HistoryListBuild(info, buffer + last, linecount++);
	free(buffer);
	info->counthists = linecount;
	while (info->counthists-- >= HIST_MAX)
		NodeIndexDeleted(&(info->Histor), 0);
	HistoryRenumbr(info);
	return (info->counthists);
}
/**
 * HistoryListBuild - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int HistoryListBuild(t__info *info, char *buffer, int linecount)
{
	t__liste *node = NULL;

	if (info->Histor)
		node = info->Histor;
	EndAddNote(&node, buffer, linecount);

	if (!info->Histor)
		info->Histor = node;
	return (0);
}
/**
 * HistoryRenumbr - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int HistoryRenumbr(t__info *info)
{
	t__liste *node = info->Histor;
	int i = 0;

	while (node)
	{
		node->number = i++;
		node = node->next_node;
	}
	return (info->counthists = i);
}
