#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @arv: the strargument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(t__info *info, char **arv)
{
	ssize_t r = 0;
	int Bui_re = 0;

	while (r != -1 && Bui_re != -2)
	{
		InfoClearer(info);
		if (ModeIntera(info))
			InpStrPrint("$ ");
		WrCharC(BUF_FLUSH);
		r = LineInputGet(info);
		if (r != -1)
		{
			InfoStructIn(info, arv);
			Bui_re = StrBuilFound(info);
			if (Bui_re == -1)
				CmdFound(info);
		}
		else if (ModeIntera(info))
			WrCharPutC('\n');
		InfoStructFree(info, 0);
	}
	TipeHistory(info);
	InfoStructFree(info, 1);
	if (!ModeIntera(info) && info->statuus_)
		exit(info->statuus_);
	if (Bui_re == -2)
	{
		if (info->number_error == -1)
			exit(info->statuus_);
		exit(info->number_error);
	}
	return (Bui_re);
}

/**
 * StrBuilFound - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int StrBuilFound(t__info *info)
{
	int i, Bui_in_re = -1;
	builtin_table Buiintable[] = {
		{"exit", ShellExit},
		{"env", CorrentEnv},
		{"help", ChangeHelp},
		{"Histor", LsHistori},
		{"setenv", EnvNewVar},
		{"unsetenv", EnvVarRemove},
		{"cd", ChangeDir},
		{"alias", AliasMan},
		{NULL, NULL}
	};

	for (i = 0; Buiintable[i].type; i++)
		if (ComparStr(info->ArrArg[0], Buiintable[i].type) == 0)
		{
			info->countofline++;
			Bui_in_re = Buiintable[i].func(info);
			break;
		}
	return (Bui_in_re);
}

/**
 * CmdFound - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void CmdFound(t__info *info)
{
	char *SPath  = NULL;
	int i, k;

	info->SPath  = info->ArrArg[0];
	if (info->countlifeflags == 1)
	{
		info->countofline++;
		info->countlifeflags = 0;
	}
	for (i = 0, k = 0; info->strarg[i]; i++)
		if (!DelimCheck(info->strarg[i], " \t\n"))
			k++;
	if (!k)
		return;

	SPath = PathCmdFind(info, EnvironGet(info, "PATH="), info->ArrArg[0]);
	if (SPath)
	{
		info->SPath = SPath;
		CmdFork(info);
	}
	else
	{
		if ((ModeIntera(info) || EnvironGet(info, "PATH=")
			|| info->ArrArg[0][0] == '/') && Comm_IS(info, info->ArrArg[0]))
			CmdFork(info);
		else if (*(info->strarg) != '\n')
		{
			info->statuus_ = 127;
			ErrorMessPrint(info, "not found\n");
		}
	}
}

/**
 * CmdFork - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void CmdFork(t__info *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->SPath, info->ArrArg
		, StrArrayEnv(info)) == -1)
		{
			InfoStructFree(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->statuus_));
		if (WIFEXITED(info->statuus_))
		{
			info->statuus_ = WEXITSTATUS(info->statuus_);
			if (info->statuus_ == 126)
				ErrorMessPrint(info, "Permission denied\n");
		}
	}
}
