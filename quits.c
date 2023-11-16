#include "shell.h"

/**
 *_cpstr - function that duplicates a string
 *@tcp: copy to
 *@fcp: copy from
 *@cnt: the counts of characters to be duplicated
 *Return: the string
 *Authors: Kelvin Njuiri and Bismark Kete
 */
char *_cpstr(char *tcp, char *fcp, int cnt)
{
	char *str = tcp;
	int ind = 0, index;

	while (fcp[ind] != '\0' && ind < cnt - 1)
	{
		tcp[ind] = fcp[ind];
		ind++;
	}
	if (ind < cnt)
	{
		index = ind;
		while (index < cnt)
		{
			tcp[index] = '\0';
			index++;
		}
	}
	return (str);
}

/**
 *_cnstr - function to cnt strings
 *@tcp: string one
 *@fcp: string two
 *@cnt: bytes
 *Return: the final string after the concat.
 */
char *_cnstr(char *tcp, char *fcp, int cnt)
{
	char *str = tcp;
	int ind = 0, index = 0;

	while (tcp[ind] != '\0')
		ind++;
	while (fcp[index] != '\0' && index < cnt)
	{
		tcp[ind] = fcp[index];
		ind++;
		index++;
	}
	if (index < cnt)
		tcp[ind] = '\0';
	return (str);
}

/**
 *_fndch - finds a character
 *@str: the string to search in
 *@ch: the expected character been looked for
 *Return: string's pointer
 */
char *_fndch(char *str, char ch)
{
	do {
		if (ch == *str)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

