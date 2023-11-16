#ifndef HEADER_FILE_SHELL
#define HEADER_FILE_SHELL

/******************** Standard libraries **********************/
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>

extern char **environ;

#define BFR_SZ_DSP 1024
#define BFR_SZ_WRT 1024
#define FLS_BFR -1
#define CMD_NORM	0
#define COMMAND_R	1
#define COMMAND_A	2
#define COMMAND_C	3
#define LWRCS_CNV	1
#define UNS_CNV	2
#define FNC_GT 0
#define USE_STRTOK 0
#define PAST_FL	".simple_shell_history"
#define PAST_M	4096

#define NOTI_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - structure
 *@arg: arguments
 *@argv: argument vector
 *@path: location
 *@argc: number of arguments
 *@line_count: number of error
 *@err_num: exit code for errors
 *@linecount_flag: number of lines
 *@fname: name of file
 *@env: environment
 *@environ: environment
 *@history: recent kept
 *@alias: also known as
 *@env_changed: new environment
 *@status: status for return
 *@cmd_buf: buffer
 *@cmd_buf_type: type
 *@readfd: file descriptor
 *@histcount: recent records
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
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

/**
 *struct builtin - structure
 *@type: type
 *@func: method
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/*********************** Prototypes for shell_loop.c **************/
int _bltnfd(info_t *);
void _fkexc(info_t *);
int _mnshl(info_t *, char **);
void _fdexc(info_t *);

/*********************** Prototyoes for parser.c ******************/
int _isexc(info_t *, char *);
char *_fdpth(info_t *, char *, char *);
char *_chrdp(char *, int, int);

/*********************** Prototypes for errors.c ******************/
int _w_dsc(char ch, int dsc);
void _errp(char *);
int _wtdsc(char *s, int dsc);
int _errptch(char);

/*********************** Prototypes for string.c ******************/
char *_strcnct(char *, char *);
int _compstr(char *, char *);
char *_wtstr(const char *, const char *);
int _lngthstr(char *);

/****************** Prototypes for string1.c ***********************/
void _prnt(char *);
char *_cpst(char *, char *);
int _chprnt(char);
char *_mulst(const char *);

/******************* Prototypes for exits.c   **********************/
char *_fndch(char *, char);
char *_cpstr(char *, char *, int);
char *_cnstr(char *, char *, int);

/******************* Prototypes for tokenizer.c ********************/
char **_dvst(char *, char *);
char **_dvst2(char *, char);

/******************** Prototypes for realloc.c *********************/
char *_balmem(char *, char, unsigned int);
void set_fr(char **);
void *r_alc(void *, unsigned int, unsigned int);

/******************** Prototypes for memory.c **********************/
int fr_mem(void **);

/********************* Prototypes for _atoi.c *********************/
int _comint(info_t *);
int _delimeter(char, char *);
int _atoi(char *);
int _Alph(int);

/********************* Prototypes for errors1.c *********************/
void _igncmt(char *);
void _errout(info_t *, char *);
int _estoi(char *);
int _decprt(int, int);
char *cnvntoa(long int, int, int);

/********************* Prototypes for builtin.c *********************/
int _help(info_t *);
int _q_ext(info_t *);
int _cdchn(info_t *);

/********************* Prototypes for builtin1.c ********************/
int _shwhstry(info_t *);
int _alsknw(info_t *);
int _rm_alsknw(info_t *, char *s);
int _crt_alsknw(info_t *, char *s);
int out_alsknw(list_t *);

/******************* Prototypes for getline.c **********************/
ssize_t _gtentered(info_t *);
void _manipulator(int);
int _brnln(info_t *, char **, size_t *);

/******************** Prototypes for getinfo.c *******************/
void _fr_strt(info_t *, int);
void _inistrt(info_t *);
void _s_strt(info_t *, char **);

/******************** Prototypes for _environ.c ******************/
int _unsetenv(info_t *);
int _env(info_t *);
int _envlt(info_t *);
int _setenv(info_t *);
char *_gt_env(info_t *, const char *);

/********************* Prototypes for getenv.c *******************/
char **_envg(info_t *);
int _senv(info_t *, char *, char *);
int _usenv(info_t *, char *);

/******************** Prototypes for history.c *******************/
char *_spast(info_t *);
int _crtpast(info_t *);
int _thrpast(info_t *);
int _fnlspast(info_t *, char *, int);
int _rpast(info_t *);

/********************* Prototypes for lists.c ********************/
list_t *_nad(list_t **, const char *, int);
list_t *_down_ad(list_t **, const char *, int);
size_t _lstrprnt(const list_t *);
int _rmnd(list_t **, unsigned int);
void _allwlt(list_t **);

/******************** Prototypes for lists1.c *********************/
size_t _lnlt(const list_t *);
list_t *_ndstw(list_t *, char *, char);
char **_strlt(list_t *);
ssize_t _gni(list_t *, list_t *);
size_t _lsprnt(const list_t *);

/********************* Prototypes for vars.c **********************/
int _rpstr(char **, char *);
int _rp_alsknw(info_t *);
int _bfrchn(info_t *, char *, size_t *);
int _rplv(info_t *);
void cnt_chn(info_t *, char *, size_t *, size_t, size_t);

#endif  /* Simple Shell project authors: Kelvin Njuiri and Bismark Kete */
