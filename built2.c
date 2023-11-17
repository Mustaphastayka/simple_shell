#include "shell.h"

int LsHistori(t__info *info)
{
	PrintListsCon(info->Histor);
	return (0);
}

int unset_alias(t__info *info, char *str)
{
	char *p, c;
	int ter;

	p = FoundCharInString(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ter = NodeIndexDeleted(&(info->Alias),
												IndexNodeGet(info->Alias, NodePrefStart(info->Alias, str, -1)));
	*p = c;
	return (ter);
}

int set_alias(t__info *info, char *str)
{
	char *p;

	p = FoundCharInString(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (EndAddNote(&(info->Alias), str, 0) == NULL);
}

int print_alias(t__liste *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = FoundCharInString(node->str, '=');
		for (a = node->str; a <= p; a++)
			WrCharPutC(*a);
		WrCharPutC('\'');
		InpStrPrint(p + 1);
		InpStrPrint("'\n");
		return (0);
	}
	return (1);
}

int AliasMan(t__info *info)
{
	int i = 0;
	char *p = NULL;
	t__liste *node = NULL;

	if (info->CountArg == 1)
	{
		node = info->Alias;
		while (node)
		{
			print_alias(node);
			node = node->next_node;
		}
		return (0);
	}
	for (i = 1; info->ArrArg[i]; i++)
	{
		p = FoundCharInString(info->ArrArg[i], '=');
		if (p)
			set_alias(info, info->ArrArg[i]);
		else
			print_alias(NodePrefStart(info->Alias, info->ArrArg[i], '='));
	}

	return (0);
}
