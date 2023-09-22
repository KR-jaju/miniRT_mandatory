#include "libds.h"

bool	queue_is_empty(t_queue *this)
{
	return (this->count == 0);
}

bool	queue_is_full(t_queue *this)
{
	return (this->count == this->capacity);
}
