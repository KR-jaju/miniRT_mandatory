
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "libds.h"
#include "libft.h"

static
bool	list_resize(t_list *this, size_t new_size)
{
	uint8_t*const	new = malloc(new_capacity * this->type_size);

	if (new == (void *)0)
		return (false);
	if (new_size < this->count)
		this->count = new_size;
	this->capacity = new_size;
	ft_memmove(new, this->data, this->count * this->type_size);
	free(this->data);
	this->data = new;
	return (true);
}

bool	list_init(t_list *this, size_t type_size, size_t capacity)
{
	this->data = malloc(type_size * capacity);
	if (this->data == (void *)0)
		return (0);
	this->type_size = type_size;
	this->capacity = capacity;
	this->count = 0;
	return (1);
}

bool	list_push(t_list *this, void *data)
{
	if (this->data == (void *)0)
		return (false);
	if (this->count == this->capacity)
		if (!list_resize(this, this->capacity * 2))
			return (false);
	ft_memmove(&this->data[this->count * this->type_size], data,
		this->type_size);
	this->count++;
	return (true);
}

bool	list_set(t_list *this, uint32_t idx, void *data)
{
	if (idx < 0 || this->capacity <= idx)
		return (false);
	ft_memmove(&this->data[idx * this->type_size], data, this->type_size);
	return (true);
}

bool	list_get(t_list *this, uint32_t idx, void *out)
{
	if (idx < 0 || this->capacity <= idx)
		return (false);
	ft_memmove(out, &this->data[idx * this->type_size], this->type_size);
	return (true);
}

void	*list_collect(t_list *this, uint32_t *len)
{
	uint8_t*const	new = malloc(this->count * this->type_size);

	if (new == (void *)0)
		return ((void *)0);
	if (len != (void *)0)
		*len = this->count;
	ft_memmove(new, this->data, this->count * this->type_size);
	return (new);
}
