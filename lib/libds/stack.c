#include "libds.h"

void	stack_resize(t_stack *this, size_t new_size)
{
	uint8_t*const	new = allocate(new_size * this->count);

	if (new_size < this->count)
		this->count = new_size;
	this->capacity = new_size;
	ft_memcpy(new, this->data, this->count * this->type_size);
	free(this->data);
	this->data = new;
}

void	stack_init(t_stack *this, size_t type_size, size_t capacity)
{
	this->data = allocate(type_size * capacity);
	this->type_size = type_size;
	this->count = 0;
	this->capacity = capacity;
	this->top = 0;
}

bool	stack_is_empty(t_stack *this)
{
	return (this->count == 0);
}

bool	stack_is_full(t_stack *this)
{
	return (this->count == this->capacity);
}

void	stack_push(t_stack *this, void *elem)
{
	if (this->count == this->capacity)
		stack_resize(this, this->capacity * 2);
	ft_memmove(&this->data[this->count * this->type_size], \
				elem, this->type_size);
    this->count++;
    this->top = this->type_size * (this->count - 1);
}

void	*stack_pop(t_stack *this)
{
	uint8_t	*elem;

	if (this->count == 0)
		return ;
	elem = allocate(this->type_size);
	ft_memcpy(elem, this->data[this->top], this->type_size);
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
