
#ifndef BUFFER_H
# define BUFFER_H

# include <stdint.h>
# include <stddef.h>

typedef struct s_buffer
{
	uint8_t	*data;
	size_t	type_size;
	size_t	length;
	size_t	capacity;
}t_buffer;

void	buffer_init(t_buffer *this, size_t type_size, size_t capacity);
void	buffer_push(t_buffer *this, void *data);
void	*buffer_collect(t_buffer *this, size_t *len);


#endif
