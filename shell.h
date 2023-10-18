#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>



#define BUFF_FLCH -1
#define R_BUFF_SIZE 1024
#define W_BUFF_SIZE 1024


#define CMD_NORM	0
#define CMD_CHAIN	3
#define CMD_AND 2
#define CMD_OR 1



#define COV_LCASE	1
#define COV_UNSGND	2


#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_history"
#define USE_STRTOK 0
#define USE_GETLINE 0



extern char **environ;


/**
 * struct liststr - singly linked list
 * @numb: the number input 
 * @strng: a string
 * @next: points to the next node
 */
typedef struct liststring
{
	int numb;
	char *strng;
	struct liststring*next;
} liststr_t;

/**
 *struct passinfo - a struct
 *@arg: aargument
 *@argv: argument variable
 *@cmd_buf: points to buffer
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd:file description
 *@histcount: history line counter
 *@path: path
 *@argc: arg count
 *@line_count: the error count
 *@env_changed: on if environ was changed
 *@err_num:error number
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom environment
 *@history:history of node
 *@alias: the alias node
 *@status: command status
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	liststr_t *env;
	liststr_t  *history;
	liststr_t  *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
        int (*func)(info_t *);
	
} builtin_table;


/* hshfile.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void cmdfork(info_t *);  

/* pathfile.c */
int excut_cmd(info_t *, char *);
char *duplchar(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophshfile.c */
int loophsh(char **);

/* string_functions_error.c */
void _strputs(char *);
int _eputchar(char);
int _putfildescriptor(char c, int fd);
int _putsfd(char *str, int fd);

/* str_functions_file.c */
int _stringleng(char *);
int _strcompar(char *, char *);
char *starts_with_char(const char *, const char *);
char *_stringconcat(char *, char *);

/* str_functions2file.c */
char *_strngcopy (char *, char *);
char *_strngduplic(const char *);
void _puts(char *);
int _putchar(char);

/* str_functions3_file.c */
char *_strngcopi(char *, char *, int);
char *_strngconcat(char *, char *, int);
char *_strngcharct(char *, char);

/* str_functions4_file.c */
char **stringsplit(char *, char *);
char **stringsplit2(char *, char);

/* memo_functions_file */
char *_memoset(char *, char, unsigned int);
void _memofree(char **);
void *_realloctmem(void *, unsigned int, unsigned int);

/* memo_functions2_file.c */
int pointfree(void **);

/* more_funs_file.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _ston(char *);

/* more_funs2_file.c */
int _errston(char *);
void print_error(info_t *, char *);
int prntdec(int, int);
char *convnum(long int, int, int);
void remcom(char *);

/* builtin_emulat_file.c */
int exshell(info_t *);
int changdir(info_t *);
int hlp(info_t *);

/* builtin_emulat2_file.c */
int myhist(info_t *);
int alis(info_t *);

/* get_line_file.c module */
ssize_t gitinput(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
ssize_t readbuffer(info_t *, char *, size_t *);

/* info_file.c module */
void clrinfo(info_t *);
void settinfo(info_t *, char **);
void freinfo(info_t *, int);

/* envo_file.c module */
char *_getenvironment(info_t *, const char *);
int _myenvironment(info_t *);
int _mysetenviron(info_t *);
int _myunsetenv(info_t *);
int populate_envo(info_t *);

/* envo2_file.c module */
char **getEnvironment(info_t *);
int _unsetenvironment(info_t *, char *);
int _setenvironment(info_t *, char *, char *);


/* functions_io_file.c */
char *git_fil_hist(info_t *info);
int create_hist(info_t *info);
int redhist(info_t *info);
int build_hist (info_t *info, char *buf, int linecount);
int renew_hist(info_t *info);

/* liststring_file.c module */
liststr_t *adnod(liststr_t **, const char *, int);
liststr_t *adnodend(liststr_t **, const char *, int);
size_t prntlststring(const liststr_t *);
int delnod(liststr_t **, unsigned int);
void frlst(liststr_t **);

/* liststring2_file.c module */
size_t length_of_list(const liststr_t *);
char **ltos(liststr_t *);
size_t prent_lest(const liststr_t *);
liststr_t *ThenodeStartsWith(liststr_t *, char *, char);
ssize_t get_index_of_node(liststr_t *, liststr_t *);

/* chain_file.c */
int mychain(info_t *, char *, size_t *);
void ckchain(info_t *, char *, size_t *, size_t, size_t);
int repalias(info_t *);
int repvars (info_t *);
int repstring(char **, char *);

#endif
