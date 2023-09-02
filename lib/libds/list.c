
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "libds.h"
#include "libft.h"

static
int	list_resize(t_list *this, size_t new_capacity)
{
	uint8_t*const	new = malloc(new_capacity * this->type_size);

	if (new == (void *)0)
		return (false);
	if (new_capacity < this->count)
		this->count = new_capacity;
	this->capacity = new_capacity;
	ft_memmove(new, this->data, this->count * this->type_size);
	free(this->data);
	this->data = new;
	return (true);
}

int	list_init(t_list *this, size_t type_size, size_t capacity)
{
	this->data = malloc(type_size * capacity);
	if (this->data == (void *)0)
		return (-1);
	this->type_size = type_size;
	this->capacity = capacity;
	this->count = 0;
	return (0);
}

int	list_push(t_list *this, void *data)
{
	if (this->data == (void *)0)
		return (-1);
	if (this->count == this->capacity)
		if (list_resize(this, this->capacity * 2) == -1)
			return (-1);
	ft_memmove(&this->data[this->count * this->type_size], data,
		this->type_size);
	this->count++;
	return (0);
}

int	list_set(t_list *this, uint32_t idx, void *data)
{
	if (this->data == (void *)0)
		return (-1);
	if (idx < 0 || this->capacity <= idx)
		return (-1);
	ft_memmove(&this->data[idx * this->type_size], data, this->type_size);
	return (0);
}

int	list_get(t_list *this, uint32_t idx, void *out)
{
	if (this->data == (void *)0)
		return (-1);
	if (idx < 0 || this->capacity <= idx)
		return (-1);
	ft_memmove(out, &this->data[idx * this->type_size], this->type_size);
	return (0);
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

void	list_free(t_list *this)
{
	free(this->data);
	this->capacity = 0;
	this->count = 0;
	this->type_size = 0;
}
