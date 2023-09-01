#include "libds.h"

static int	stack_resize(t_stack *this, int new_capacity)
{
	uint8_t*const	new = malloc(new_capacity * this->type_size);

	if (!new)
		return (-1);
	if (new_capacity < this->count)
		this->count = new_capacity;
	this->capacity = new_capacity;
	ft_memcpy(new, this->data, this->count * this->type_size);
	free(this->data);
	this->data = new;
	return (0);
}

int	stack_init(t_stack *this, size_t type_size, int capacity)
{
	this->data = malloc(type_size * capacity);
	if (!this->data)
		return (-1);
	this->type_size = type_size;
	this->count = 0;
	this->capacity = capacity;
	this->top = 0;
	return (0);
}

bool	stack_is_empty(t_stack *this)
{
	return (this->count == 0);
}

bool	stack_is_full(t_stack *this)
{
	return (this->count == this->capacity);
}

int	stack_push(t_stack *this, void *elem)
{
	if (this->count == this->capacity \
		|| stack_resize(this, this->capacity * 2) == -1)
		return (-1);
	ft_memmove(&this->data[this->count * this->type_size], \
				elem, this->type_size);
	this->count++;
	this->top = this->type_size * (this->count - 1);
	return (0);
}

void	*stack_pop(t_stack *this)
{
	uint8_t	*elem;

	if (this->count == 0)
		return (NULL);
	elem = malloc(this->type_size);
	if (!elem)
		return (NULL);
	ft_memcpy(elem, &this->data[this->top], this->type_size);
	this->count--;
	this->top = this->type_size * (this->count - 1);
	return ((void *)elem);
}

void	*stack_peek(t_stack *this)
{
	if (this->count == 0)
		return (NULL);
	return (&this->data[this->top]);
}
