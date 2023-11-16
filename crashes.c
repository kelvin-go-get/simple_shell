#include "shell.h"

/**
 *_errp - function that outputs
 * @s: expected string to output
 * Return: Nothing
 * Authors: Kelvin Njuiri and Bismark Kete
 */
void _errp(char *s)
{
	int index;

	index = 0;
	if (!s)
		return;

	while (s[index] != '\0')
	{
		_errptch(s[index]);
		index++;
	}
}

/**
 * _errptch - function that writes to standard error, a character
 * @ch: expected character to write
 * Return: -1 (Error), 1 (Success) and error number is set
 *			appropriately.
 */
int _errptch(char ch)
{
	static char bfr[BFR_SZ_WRT];
	static int index;

	if (index >= BFR_SZ_WRT || ch == FLS_BFR)
	{
		write(2, bfr, index);
		index = 0;
	}

	if (ch != FLS_BFR)
		bfr[index++] = ch;

	return (1);
}

/**
 * _w_dsc - writes to the file descriptor, the character
 * @ch: expected character to print
 * @dsc: the destination
 *
 * Return: 1 (Success), -1 (Error) and error number is appropriately made.
 */
int _w_dsc(char ch, int dsc)
{
	static char bfr[BFR_SZ_WRT];
	static int index;

	if (index >= BFR_SZ_WRT || ch == FLS_BFR)
	{
		write(dsc, bfr, index);
		index = 0;
	}
	if (ch != FLS_BFR)
		bfr[index++] = ch;

	return (1);
}

/**
 *_wtdsc - function that writes a string that has been typed or generated
 * @dsc: descriptor of a file
 * @s: string expected to be printed
 * Return: the counts of character printed
 */
int _wtdsc(char *s, int dsc)
{
	int index;

	index = 0;
	if (!s)
		return (0);

	while (*s)
	{
		index += _w_dsc(*s++, dsc);
	}

	return (index);
}
