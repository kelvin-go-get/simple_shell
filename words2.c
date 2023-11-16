#include "shell.h"

/**
 * _cpst - clone of the strcpy function
 * @to: arrival
 * @from: departure
 *
 * Return: arrival's pointer
 * Author: Kelvin Njuiri and Bismark Kete
 */
char *_cpst(char *to, char *from)
{
	int index;

	index = 0;
	if (from == 0 || to == from)
		return (to);
	while (from[index])
	{
		to[index] = from[index];
		index++;
	}
	to[index] = 0;
	return (to);
}

/**
 * _mulst - makes a string two
 * @s: expected string to create another from
 *
 * Return: final work's pointer
 */
char *_mulst(const char *s)
{
	char *otp;
	int ln;

	ln = 0;
	if (s == NULL)
		return (NULL);

	while (*s++)
		ln++;

	otp = malloc((ln + 1) * sizeof(char));
	if (!otp)
		return (NULL);

	for (ln++; ln--;)
		otp[ln] = *--s;

	return (otp);
}

/**
 *_prnt - outputs any good thing that has been entered
 *@s: expected thing to be printed
 *
 * Return: void
 */
void _prnt(char *s)
{
	int index;

	index = 0;
	if (!s)
		return;
	while (s[index] != '\0')
	{
		_chprnt(s[index]);
		index++;
	}
}

/**
 * _chprnt - writes to standard output, the character
 * @ch: expected character to write
 *
 * Return: 1 (Success),-1 (Error) and ERRNO.
 */
int _chprnt(char ch)
{
	static char bfr[BFR_SZ_WRT];
	static int index;

	if (index >= BFR_SZ_WRT || ch == FLS_BFR)
	{
		write(1, bfr, index);
		index = 0;
	}
	if (ch != FLS_BFR)
		bfr[index++] = ch;

	return (1);
}
