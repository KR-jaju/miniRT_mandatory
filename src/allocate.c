#include <stddef.h>
#include <stdlib.h>

typedef unsigned char	t_byte;

void	*allocate(size_t size)
{
	t_byte*const	ptr = malloc(size);
	size_t			i;

	i = 0;
	if (ptr == (void *)0)
		exit(1);
	while (i < size)
	{
		ptr[i] = (t_byte)0;
		i++;
	}
	return (ptr);
}
