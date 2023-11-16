#include "shell.h"

/**
 *_balmem - setting a memory with a constant byte
 *@ptr: memory area's pointer
 *@bt: the value to fill the memory with
 *@amnt: the number of bytes to fill the memory with
 *Return: the memory area's pointer, ptr
 */
char *_balmem(char *ptr, char bt, unsigned int amnt)
{
	unsigned int index;

	for (index = 0; index < amnt; index++)
		ptr[index] = bt;
	return (ptr);
}

/**
 * set_fr - sets strings free
 * @strr: character type
 */
void set_fr(char **strr)
{
	char **x = strr;

	if (!strr)
		return;
	while (*strr)
		free(*strr++);
	free(x);
}

/**
 * r_alc - function to reallocate memory
 * @p: previously allocated memory's pointer
 * @msz: previous byte
 * @rsz: new byte
 *
 * Return: previously allocated memory's pointer
 */
void *r_alc(void *p, unsigned int msz, unsigned int rsz)
{
	char *ptr;

	if (!p)
		return (malloc(rsz));
	if (!rsz)
		return (free(p), NULL);
	if (msz == rsz)
		return (p);

	ptr = malloc(rsz);
	if (!ptr)
		return (NULL);

	msz = msz < rsz ? msz : rsz;
	while (msz--)
		ptr[msz] = ((char *)p)[msz];
	free(p);
	return (ptr);
}



