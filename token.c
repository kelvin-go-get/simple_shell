#include "shell.h"

/**
 * _dvst - divides stings
 * @s: initial
 * @del: deli
 * Return: NULL (Failure), sting address
 * Authors: Kelvin Njuiri and Bismark Kete
 */

char **_dvst(char *s, char *del)
{
	char **st;
	int a, index, x, y, cnt = 0;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (a = 0; s[a] != '\0'; a++)
		if (!_delimeter(s[a], del) && (_delimeter(s[a + 1], del) || !s[a + 1]))
			cnt++;

	if (cnt == 0)
		return (NULL);
	st = malloc(sizeof(char *) * (1 + cnt));
	if (!st)
		return (NULL);
	for (a = 0, index = 0; index < cnt; index++)
	{
		while (_delimeter(s[a], del))
			a++;
		x = 0;
		while (!_delimeter(s[a + x], del) && s[a + x])
			x++;
		st[index] = malloc((x + 1) * sizeof(char));
		if (!st[index])
		{
			for (x = 0; x < index; x++)
				free(st[x]);
			free(st);
			return (NULL);
		}
		for (y = 0; y < x; y++)
			st[index][y] = s[a++];
		st[index][y] = 0;
	}
	st[index] = NULL;
	return (st);
}

/**
 * **_dvst2 - divides sting
 * @s: initial
 * @del: del
 * Return: NULL (Failure), sting address
 */
char **_dvst2(char *s, char del)
{
	char **st;
	int index, index2, x, y, cnt = 0;

	if (s[0] == 0 || s == NULL)
		return (NULL);
	for (index = 0; s[index] != '\0'; index++)
		if ((s[index] != del && s[index + 1] == del) ||
		    (s[index] != del && !s[index + 1]) || s[index + 1] == del)
			cnt++;
	if (cnt == 0)
		return (NULL);
	st = malloc(sizeof(char *) * (1 + cnt));
	if (!st)
		return (NULL);
	for (index = 0, index2 = 0; index2 < cnt; index2++)
	{
		while (s[index] != del && s[index] == del)
			index++;
		x = 0;
		while (s[index + x] && s[index + x] != del && s[index + x] != del)
			x++;
		st[index2] = malloc(sizeof(char) * (x + 1));
		if (!st[index2])
		{
			for (x = 0; x < index2; x++)
				free(st[x]);
			free(st);
			return (NULL);
		}
		for (y = 0; y < x; y++)
			st[index2][y] = s[index++];
		st[index2][y] = 0;
	}
	st[index2] = NULL;
	return (st);
}
