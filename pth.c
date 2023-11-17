#include "shell.h"

int Comm_IS(t__info *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

char *CharsDup(char *pathstring, int startind, int stopind)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = startind; i < stopind; i++)
		if (pathstring[i] != ':')
			buf[k++] = pathstring[i];
	buf[k] = 0;
	return (buf);
}

char *PathCmdFind(t__info *info, char *pathstring, char *command)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstring)
		return (NULL);
	if ((RetuStrlen(command) > 2) && StartWHay(command, "./"))
	{
		if (Comm_IS(info, command))
			return (command);
	}
	while (1)
	{
		if (!pathstring[i] || pathstring[i] == ':')
		{
			path = CharsDup(pathstring, curr_pos, i);
			if (!*path)
				StringConc(path, command);
			else
			{
				StringConc(path, "/");
				StringConc(path, command);
			}
			if (Comm_IS(info, path))
				return (path);
			if (!pathstring[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
