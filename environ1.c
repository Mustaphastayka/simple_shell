#include "shell.h"

char **StrArrayEnv(t__info *info)
{
	if (!info->environ || info->ChangedEnvir)
	{
		info->environ = AListeToStr(info->EnvirList);
		info->ChangedEnvir = 0;
	}

	return (info->environ);
}

int EnvRemove(t__info *info, char *strvar)
{
	t__liste *node = info->EnvirList;
	size_t i = 0;
	char *p;

	if (!node || !strvar)
		return (0);

	while (node)
	{
		p = StartWHay(node->str, strvar);
		if (p && *p == '=')
		{
			info->ChangedEnvir = NodeIndexDeleted(&(info->EnvirList), i);
			i = 0;
			node = info->EnvirList;
			continue;
		}
		node = node->next_node;
		i++;
	}
	return (info->ChangedEnvir);
}

int EnvSetNew(t__info *info, char *strvar, char *varval)
{
	char *buf = NULL;
	t__liste *node;
	char *p;

	if (!strvar || !varval)
		return (0);

	buf = malloc(RetuStrlen(strvar) + RetuStrlen(varval) + 2);
	if (!buf)
		return (1);
	CpString(buf, strvar);
	StringConc(buf, "=");
	StringConc(buf, varval);
	node = info->EnvirList;
	while (node)
	{
		p = StartWHay(node->str, strvar);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->ChangedEnvir = 1;
			return (0);
		}
		node = node->next_node;
	}
	EndAddNote(&(info->EnvirList), buf, 0);
	free(buf);
	info->ChangedEnvir = 1;
	return (0);
}
