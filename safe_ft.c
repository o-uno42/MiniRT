#include "minirt.h"

void    *safe_malloc(size_t size)
{
	void *ptr = malloc(size);
	if (!ptr)
	{
		perror("Malloc failed");
		exit (EXIT_FAILURE);
	}
	return (ptr);
}