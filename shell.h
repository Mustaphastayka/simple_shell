#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct stringlit - singly linked list
 * @number: the number field
 * @str: a string
 * @next_node: points to the next node
 */

typedef struct stringlit
{
	int number;
	char *str;
	struct stringlit *next_node;
} t__liste;

/**
 *struct InfoPass - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@strarg: a string generated from getline containing arguements
 *@ArrArg: an array of strings generated from arg
 *@SPath: a string path for the current command
 *@CountArg: the argument count
 *@countofline: the error count
 *@number_error: the error code for exit()s
 *@countlifeflags: if on count this line of input
 *@NameFile: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@Histor: the history node
 *@alias: the alias node
 *@ChangedEnvir: on if environ was changed
 *@statuus_: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@BufCmdType: CMD_type ||, &&, ;
 *@FdReadinp: the fd from which to read line input
 *@counthists: the history line number count
 */

typedef struct InfoPass
{
	char *strarg;
	char **ArrArg;
	char *SPath;
	int CountArg;
	unsigned int countofline;
	int number_error;
	int countlifeflags;
	char *NameFile;
	t__liste *env;
	t__liste *Histor;
	t__liste *alias;
	char **environ;
	int ChangedEnvir;
	int statuus_;

	char **cmd_buf;
	int BufCmdType;
	int FdReadinp;
	int counthists;
} t__info;

#define INFO_INIT                                                           \
	{                                                                         \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
				0, 0, 0                                                             \
	}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(t__info *);
} builtin_table;

int hsh(t__info *, char **);
int StrBuilFound(t__info *);
void CmdFound(t__info *);
void CmdFork(t__info *);

int Comm_IS(t__info *, char *);
char *CharsDup(char *, int, int);
char *PathCmdFind(t__info *, char *, char *);

int HshLp(char **);

void StrPut(char *);
int WrCharC(char);
int WrCharCtoFD(char c, int fd);
int StrPrint(char *str, int fd);

int RetuStrlen(char *);
int ComparStr(char *, char *);
char *StartWHay(const char *, const char *);
char *StringConc(char *, char *);

char *CpString(char *, char *);
char *DuplString(const char *);
void InpStrPrint(char *);
int WrCharPutC(char);

char *CopyString(char *, char *, int);
char *Con2String(char *, char *, int);
char *FoundCharInString(char *, char);

char **SplString(char *, char *);
char **SplStringV2(char *, char);

char *MemoFileC(char *, char, unsigned int);
void StrFFree(char **);
void *RealloBlMem(void *, unsigned int, unsigned int);

int PoinFree(void **);

int ModeIntera(t__info *);
int DelimCheck(char, char *);
int AlphaCheck(int);
int StrToIn(char *);

int StrToIn2(char *);
void ErrorMessPrint(t__info *, char *);
int DecNumPrint(int, int);
char *NumberConver(long int, int, int);
void CommRemover(char *);

int ShellExit(t__info *);
int ChangeDir(t__info *);
int ChangeHelp(t__info *);

int LsHistori(t__info *);
int AliasMan(t__info *);

ssize_t LineInputGet(t__info *);
int LineGet(t__info *, char **, size_t *);
void CtrCBlock(int);

void InfoClearer(t__info *);
void InfoStructIn(t__info *, char **);
void InfoStructFree(t__info *, int);

char *EnvironGet(t__info *, const char *);
int CorrentEnv(t__info *);
int EnvNewVar(t__info *);
int EnvVarRemove(t__info *);
int EnvLinkedList(t__info *);

char **StrArrayEnv(t__info *);
int _unsetenv(t__info *, char *);
int _setenv(t__info *, char *, char *);

char *FileHistory(t__info *info);
int TipeHistory(t__info *info);
int HistoryRead(t__info *info);
int HistoryListBuild(t__info *info, char *buf, int linecount);
int HistoryRenumbr(t__info *info);

t__liste *StartAddNote(t__liste **, const char *, int);
t__liste *EndAddNote(t__liste **, const char *, int);
size_t StringListPrintOnly(const t__liste *);
int NodeIndexDeleted(t__liste **, unsigned int);
void FreesLists(t__liste **);

size_t LengthLists(const t__liste *);
char **AListeToStr(t__liste *);
size_t PrintListsCon(const t__liste *);
t__liste *NodePrefStart(t__liste *, char *, char);
ssize_t IndexNodeGet(t__liste *, t__liste *);

int Chains(t__info *, char *, size_t *);
void ChainCheck(t__info *, char *, size_t *, size_t, size_t);
int AliasReplac(t__info *);
int VarsReplac(t__info *);
int StrReplace(char **, char *);

#endif
