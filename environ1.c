#include "shell.h"
/**
 * StrArrayEnv - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **StrArrayEnv(t__info *info)
{
	if (!info->environ || info->ChangedEnvir)
	{
		info->environ = AListeToStr(info->EnvirList);
		info->ChangedEnvir = 0;
	}

	return (info->environ);
}
/**
 * EnvRemove - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @strvar: the string env var property
 */
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
/**
 * EnvSetNew - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @strvar: the string env var property
 * @varval: the string env var value
 *  Return: Always 0
 */
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
