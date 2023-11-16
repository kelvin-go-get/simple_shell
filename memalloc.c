#include "shell.h"

/**
 * fr_mem - nulls an address after freeing the pointer
 * @p: expected pointer to be freed
 *
 * Return: 1 if successful and 0, otherwise.
 */
int fr_mem(void **p)
{
	if (*p && p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}

	return (0);
}
