
#include <buffer.h>
#include <allocate.h>
#include <libft.h>

static
void	buffer_resize(t_buffer *this, size_t new_size)
{
	uint8_t*const	new = allocate(new_size * this->length);

	if (new_size < this->length)
		this->length = new_size;
	this->capacity = new_size;
	ft_memmove(new, this->data, this->length * this->length);
	free(this->data);
	this->data = new;
}

void	buffer_init(t_buffer *this, size_t type_size, size_t capacity)
{
	this->data = allocate(type_size * capacity);
	this->type_size = type_size;
	this->capacity = capacity;
	this->length = 0;
}

void	buffer_push(t_buffer *this, void *data)
{
	if (this->length == this->capacity)
		buffer_resize(this, this->capacity * 2);
	ft_memmove(&this->data[this->length * this->type_size], data,
		this->type_size);
	this->length++;
}

void	*buffer_collect(t_buffer *this, size_t *len)
{
	uint8_t*const	new = allocate(this->length * this->type_size);

	if (len != (void *)0)
		*len = this->length;
	ft_memmove(new, this->data, this->length * this->type_size);
	free(this->data);
	this->data = (void *)0;
	this->capacity = 0;
	this->length = 0;
	this->type_size = 0;
	return (new);
}