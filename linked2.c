#include "shell.h"

/**
 * _lnlt - function that finds the linked list's measurement
 * @ptr: pointer 1
 *
 * Return: the measurement
 * Author: Kelvin Njuiri and Bismark Kete
 */
size_t _lnlt(const list_t *ptr)
{
	size_t index;

	index = 0;
	while (ptr)
	{
		ptr = ptr->next;
		index++;
	}

	return (index);
}

/**
 * _strlt - brings out the list's strings
 * @frst: first node
 *
 * Return: array of strings
 */
char **_strlt(list_t *frst)
{
	char *sptr1;
	list_t *n = frst;
	char **sptr2;
	size_t index, index2;

	index = _lnlt(frst);
	sptr2 = malloc((index + 1) * sizeof(char *));
	if (!sptr2)
		return (NULL);
	if (!index || !frst)
		return (NULL);
	for (index = 0; n; n = n->next, index++)
	{
		sptr1 = malloc(_lngthstr(n->str) + 1);
		if (!sptr1)
		{
			for (index2 = 0; index2 < index; index2++)
				free(sptr2[index2]);
			free(sptr2);
			return (NULL);
		}

		sptr1 = _cpst(sptr1, n->str);
		sptr2[index] = sptr1;
	}
	sptr2[index] = NULL;

	return (sptr2);
}


/**
 * _lsprnt - outputs the contents of a linked list
 * @frst: beginning
 * Return: linked list's measurement
 */
size_t _lsprnt(const list_t *frst)
{
	size_t index;

	index = 0;
	while (frst)
	{
		_prnt(cnvntoa(frst->num, 10, 0));
		_chprnt(':');
		_chprnt(' ');
		_prnt(frst->str ? frst->str : "(nil)");
		_prnt("\n");
		frst = frst->next;
		index++;
	}
	return (index);
}

/**
 * _ndstw - function that returns n
 * @n: pointer
 * @before: initial
 * @ch: next char
 * Return: NULL or n
 */
list_t *_ndstw(list_t *n, char *before, char ch)
{
	char *ptr = NULL;

	while (n)
	{
		ptr = _wtstr(n->str, before);
		if (ptr && ((*ptr == ch) || (ch == -1)))
			return (n);
		n = n->next;
	}
	return (NULL);
}

/**
 * _gni - finds the position of the node
 * @frst: beginning's pointer
 * @n: the n's pointer
 *
 * Return: -1 and the position of node
 */
ssize_t _gni(list_t *frst, list_t *n)
{
	size_t index;

	index = 0;
	while (frst)
	{
		if (n == frst)
			return (index);
		frst = frst->next;
		index++;
	}

	return (-1);
}
