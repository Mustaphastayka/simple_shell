#include "shell.h"
/**
 * InfoClearer - initializes info_t struct
 * @info: struct address
 */
void InfoClearer(t__info *info)
{
	info->strarg = NULL;
	info->ArrArg = NULL;
	info->SPath = NULL;
	info->CountArg = 0;
}
/**
 * InfoStructIn - initializes info_t struct
 * @info: struct address
 * @arv: argument vector
 */
void InfoStructIn(t__info *info, char **arv)
{
	int i = 0;

	info->NameFile = arv[0];
	if (info->strarg)
	{
		info->ArrArg = SplString(info->strarg, " \t");
		if (!info->ArrArg)
		{

			info->ArrArg = malloc(sizeof(char *) * 2);
			if (info->ArrArg)
			{
				info->ArrArg[0] = DuplString(info->strarg);
				info->ArrArg[1] = NULL;
			}
		}
		for (i = 0; info->ArrArg && info->ArrArg[i]; i++)
			;
		info->CountArg = i;

		AliasReplac(info);
		VarsReplac(info);
	}
}
/**
 * InfoStructFree - frees info_t struct fields
 * @info: struct address
 * @allfi: true if freeing all fields
 */
void InfoStructFree(t__info *info, int allfi)
{
	StrFFree(info->ArrArg);
	info->ArrArg = NULL;
	info->SPath = NULL;
	if (allfi)
	{
		if (!info->cmd_buf)
			free(info->strarg);
		if (info->EnvirList)
			FreesLists(&(info->EnvirList));
		if (info->Histor)
			FreesLists(&(info->Histor));
		if (info->Alias)
			FreesLists(&(info->Alias));
		StrFFree(info->environ);
		info->environ = NULL;
		PoinFree((void **)info->cmd_buf);
		if (info->FdReadinp > 2)
			close(info->FdReadinp);
		WrCharPutC(BUF_FLUSH);
	}
}
