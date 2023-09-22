#include "libds.h"

bool	stack_is_empty(t_stack *this)
{
	return (this->count == 0);
}

bool	stack_is_full(t_stack *this)
{
	return (this->count == this->capacity);
}
