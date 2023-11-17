#include "shell.h"

int CorrentEnv(t__info *info)
{
	StringListPrintOnly(info->EnvirList);
	return (0);
}

char *EnvironGet(t__info *info, const char *varname)
{
	t__liste *node = info->EnvirList;
	char *p;

	while (node)
	{
		p = StartWHay(node->str, varname);
		if (p && *p)
			return (p);
		node = node->next_node;
	}
	return (NULL);
}

int EnvNewVar(t__info *info)
{
	if (info->CountArg != 3)
	{
		StrPut("Incorrect number of arguements\n");
		return (1);
	}
	if (EnvSetNew(info, info->ArrArg[1], info->ArrArg[2]))
		return (0);
	return (1);
}

int EnvVarRemove(t__info *info)
{
	int i;

	if (info->CountArg == 1)
	{
		StrPut("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->CountArg; i++)
		EnvRemove(info, info->ArrArg[i]);

	return (0);
}

int EnvLinkedList(t__info *info)
{
	t__liste *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		EndAddNote(&node, environ[i], 0);
	info->EnvirList = node;
	return (0);
}
