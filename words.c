#include "shell.h"

/**
 * _lngthstr - fucntion that returns the counts of string
 * @str: the expected string to calculate it's length
 * Return: length of string
 * Authors: Kelvin Njuiri and Bismark Kwaku
 */
int _lngthstr(char *str)
{
	int index;

	index = 0;
	if (!str)
		return (0);

	while (*str++)
		index++;

	return (index);
}

/**
 * _compstr - compares two strings.
 * @str1: string 1
 * @str2: string 2
 *
 * Return: - if str1 < str2, + if str1 > str2, neutral(0) if str1 == str2
 */
int _compstr(char *str1, char *str2)
{
	while (*str2 && *str1)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str2++;
		str1++;
	}
	if (*str2 == *str1)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * _wtstr - checks for a string
 * @h: string we are looking through
 * @n: the string in a string we are to find
 *
 * Return: next h character's address
 */
char *_wtstr(const char *h, const char *n)
{
	while (*n)
		if (*n++ != *h++)
			return (NULL);
	return ((char *)h);
}

/**
 * _strcnct - strings concatenating
 * @to: final
 * @from: initial
 *
 * Return: final's pointer
 */
char *_strcnct(char *to, char *from)
{
	char *rtn_value = to;

	while (*to)
		to++;
	while (*from)
		*to++ = *from++;
	*to = *from;
	return (rtn_value);
}
