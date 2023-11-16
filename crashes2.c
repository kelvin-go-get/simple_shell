#include "shell.h"

/**
 * _estoi - converts to numbers, a word
 * @str: expected string to be converted into an integer
 * Return: result, 0 (No number found) or 1 (Error)
 * Authors: Kelvin Njuiri and Bismark Kete
 */
int _estoi(char *str)
{
	unsigned long int outcome;
	int index;

	index = 0, outcome = 0;
	if (*str == '+')
		str++;

	for (index = 0;  str[index] != '\0'; index++)
	{
		if (str[index] <= '9' && str[index] >= '0')
		{
			outcome = outcome * 10;
			outcome += (str[index] - '0');
			if (outcome > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (outcome);
}

/**
 * _errout - outputs a message (failure)
 * @noti: structure
 * @serr: the exact string causing failure / error
 * Return: 0 (Numbers), error string or -1 (Error)
 */
void _errout(info_t *noti, char *serr)
{
	_errp(noti->fname);
	_errp(": ");
	_decprt(noti->line_count, STDERR_FILENO);
	_errp(": ");
	_errp(noti->argv[0]);
	_errp(": ");
	_errp(serr);
}

/**
 * _decprt - function that outputs a number in base ten
 * @ipt: entered
 * @dsc: where we are writing to
 * Return: counts of output characters
 */
int _decprt(int ipt, int dsc)
{
	unsigned int now, pacs;
	int index, cnt;
	int (*__putchar)(char) = _chprnt;

	cnt = 0;
	if (dsc == STDERR_FILENO)
		__putchar = _errptch;
	if (ipt < 0)
	{
		pacs = -ipt;
		__putchar('-');
		cnt++;
	}
	else
		pacs = ipt;
	now = pacs;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (pacs / index)
		{
			__putchar('0' + now / index);
			cnt++;
		}
		now = now % index;
	}
	__putchar('0' + now);
	cnt++;

	return (cnt);
}

/**
 * cnvntoa - itoa function's replica
 * @n: numeral
 * @bs: the numeral's base
 * @flg: flags
 * Return: a outcome of the convertion
 */
char *cnvntoa(long int n, int bs, int flg)
{
	char *p;
	static char bfr[50];
	char sym;
	static char *box;
	unsigned long figure;

	figure = n;
	sym = 0;
	if (n < 0 && !(flg & UNS_CNV))
	{
		figure = -n;
		sym = '-';
	}
	box = flg & LWRCS_CNV ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &bfr[49];
	*p = '\0';

	do	{
		*--p = box[figure % bs];
		figure /= bs;
	} while (figure != 0);

	if (sym)
		*--p = sym;
	return (p);
}

/**
 * _igncmt - function to change comments
 * @adstr: address
 * Return: Always 0 (Success)
 */
void _igncmt(char *adstr)
{
	int index;

	for (index = 0; adstr[index] != '\0'; index++)
		if (adstr[index] == '#' && (adstr[index - 1] == ' ' || !index))
		{
			adstr[index] = '\0';
			break;
		}
}
