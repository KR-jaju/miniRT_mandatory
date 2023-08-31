
#include "alloc.h"
#include <stdint.h>
#include <stdlib.h>

void	*alloc(size_t size)
{
	uint8_t*const	ptr = malloc(size);
	size_t			i;

	if (ptr == (void *)0)
		exit(1);
	i = 0;
	while (i < size)
	{
		ptr[i] = (uint8_t)0;
		i++;
	}
	return (ptr);
}
