#include "libds.h"
/*
stack_init
stack_push
stack_pop
stack_peek
stack_is_empty
stack_is_full
*/

typedef struct s_stack
{
	uint8_t		*data;
	size_t		type_size;
	size_t		top;
	uint32_t	count;
	uint32_t	capacity;
}t_stack;

void	stack_resize(t_stack *this, size_t new_size)
{
	uint8_t*const	new = allocate(new_size * this->count);

	if (new_size < this->count)
		this->count = new_size;
	this->capacity = new_size;
	ft_memmove(new, this->data, this->count * this->type_size);
	free(this->data);
	this->data = new;
}

void	stack_init(t_stack *this, size_t type_size, size_t capacity)
{
	this->data = allocate(type_size * capacity);
	this->type_size = type_size;
    stack->top = 0;
    stack->count = 0;
    stack->capacity = capacity;
}

void	stack_is_empty()
{
	return (stack->count == 0);
}

void	stack_is_full()
{
	return (stack->count == stack->capacity);
}

void	stack_push(t_stack *this, void *data)
{
	if (this->count == this->capacity)
		stack_resize(this, this->capacity * 2);
	ft_memmove(&this->data[this->count * this->type_size], data,
		this->type_size);
    this->top++;
    this->count++;
}

void	*stack_pop()
{
	if (this->count < 0)
		return ;
	
}

void	stack_peek()
{

}