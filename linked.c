#include "shell.h"

/**
 * _nad - creates a new node to the linked list
 * @bgn: the beginning's pointer
 * @s: the string part
 * @itg: position of node
 * Return: counts of the contents in the structure
 * Authors: Kelvin Njuiri and Bismark Kete
 */
list_t *_nad(list_t **bgn, const char *s, int itg)
{
	list_t *fresh;

	fresh = malloc(sizeof(list_t));
	if (!fresh)
		return (NULL);
	if (!bgn)
		return (NULL);
	_balmem((void *)fresh, 0, sizeof(list_t));
	fresh->num = itg;
	if (s)
	{
		fresh->str = _mulst(s);
		if (!fresh->str)
		{
			free(fresh);
			return (NULL);
		}
	}
	fresh->next = *bgn;
	*bgn = fresh;
	return (fresh);
}

/**
 * _down_ad - puts at the bottom of a list, a node
 * @bgn: the beginning's address
 * @s: the string part
 * @itg: the position of the node
 * Return: counts of the contents in the structure
 */
list_t *_down_ad(list_t **bgn, const char *s, int itg)
{
	list_t *fresh;
	list_t *n;

	if (!bgn)
		return (NULL);

	n = *bgn;
	fresh = malloc(sizeof(list_t));
	if (!fresh)
		return (NULL);
	_balmem((void *)fresh, 0, sizeof(list_t));
	fresh->num = itg;
	if (s)
	{
		fresh->str = _mulst(s);
		if (!fresh->str)
		{
			free(fresh);
			return (NULL);
		}
	}
	if (n)
	{
		while (n->next)
			n = n->next;
		n->next = fresh;
	}
	else
		*bgn = fresh;

	return (fresh);
}

/**
 * _lstrprnt - outputs the contents of the list
 * @bgn: the beginning
 * Return: counts of the list
 */
size_t _lstrprnt(const list_t *bgn)
{
	size_t index;

	index = 0;
	while (bgn)
	{
		_prnt(bgn->str ? bgn->str : "(nil)");
		_prnt("\n");
		bgn = bgn->next;
		index++;
	}

	return (index);
}

/**
 * _rmnd - removes a particular element
 * @bgn: the beginning's pointer
 * @pos: position
 * Return: 1 (success) or 0 (failure)
 */
int _rmnd(list_t **bgn, unsigned int pos)
{
	unsigned int ind = 0;
	list_t *n;
	list_t *old_one;

	ind = 0;
	if (!*bgn || !bgn)
		return (0);

	if (!pos)
	{
		n = *bgn;
		*bgn = (*bgn)->next;
		free(n->str);
		free(n);
		return (1);
	}
	n = *bgn;
	while (n)
	{
		if (pos == ind)
		{
			old_one->next = n->next;
			free(n->str);
			free(n);
			return (1);
		}
		ind++;
		old_one = n;
		n = n->next;
	}
	return (0);
}

/**
 * _allwlt - empties all the list
 * @bgn_p: beginning's pointer
 * Return: nothing
 */
void _allwlt(list_t **bgn_p)
{
	list_t *n;
	list_t *another_one;
	list_t *bgn;

	if (!*bgn_p || !bgn_p)
		return;
	bgn = *bgn_p;
	n = bgn;
	while (n)
	{
		another_one = n->next;
		free(n->str);
		free(n);
		n = another_one;
	}

	*bgn_p = NULL;
}
