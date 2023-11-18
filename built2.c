#include "shell.h"
/**
 * LsHistori - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int LsHistori(t__info *info)
{
	PrintListsCon(info->Histor);
	return (0);
}
/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(t__info *info, char *str)
{
	char *p, c;
	int ter;

	p = FoundCharInString(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ter = NodeIndexDeleted(&(info->alias),
												IndexNodeGet(info->alias, NodePrefStart(info->alias, str, -1)));
	*p = c;
	return (ter);
}
/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(t__info *info, char *str)
{
	char *p;

	p = FoundCharInString(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (EndAddNote(&(info->alias), str, 0) == NULL);
}
/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
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
/**
 * AliasMan - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int AliasMan(t__info *info)
{
	int i = 0;
	char *p = NULL;
	t__liste *node = NULL;

	if (info->CountArg == 1)
	{
		node = info->alias;
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
			print_alias(NodePrefStart(info->alias, info->ArrArg[i], '='));
	}

	return (0);
}
