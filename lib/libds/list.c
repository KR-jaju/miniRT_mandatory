
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include "libds.h"
#include "alloc.h"
#include "libft.h"

static
void	list_resize(t_list *this, size_t new_size)
{
	uint8_t*const	new = alloc(new_size * this->count);

	if (new_size < this->count)
		this->count = new_size;
	this->capacity = new_size;
	ft_memmove(new, this->data, this->count * this->type_size);
	free(this->data);
	this->data = new;
}

void	list_init(t_list *this, size_t type_size, size_t capacity)
{
	this->data = allocate(type_size * capacity);
	this->type_size = type_size;
	this->capacity = capacity;
	this->count = 0;
}

void	list_push(t_list *this, void *data)
{
	if (this->count == this->capacity)
		buffer_resize(this, this->capacity * 2);
	ft_memmove(&this->data[this->count * this->type_size], data,
		this->type_size);
	this->count++;
}

void	list_set(t_list *this, uint32_t idx, void *data)
{
	ft_memmove(&this->data[idx * this->type_size], data, this->type_size);
}

void	list_get(t_list *this, uint32_t idx, void *out)
{
	ft_memmove(out, &this->data[idx * this->type_size], this->type_size);
}

void	*list_collect(t_list *this, uint32_t *len)
{
	uint8_t*const	new = alloc(this->count * this->type_size);

	if (len != (void *)0)
		*len = this->count;
	ft_memmove(new, this->data, this->count * this->type_size);
	free(this->data);
	this->data = (void *)0;
	this->capacity = 0;
	this->count = 0;
	this->type_size = 0;
	return (new);
}
