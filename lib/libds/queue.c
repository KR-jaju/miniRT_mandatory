#include "libds.h"

void	queue_resize(t_queue *this, size_t new_size)
{
	uint8_t*const	new = allocate(new_size * this->count);

	if (new_size < this->count)
		this->count = new_size;
	this->capacity = new_size;
	ft_memcpy(new, this->data, this->count * this->type_size);
	free(this->data);
	this->data = new;
}

void	queue_init(t_queue *this, size_t type_size, size_t capacity)
{
	this->data = allocate(type_size * capacity);
	this->type_size = type_size;
	this->count = 0;
	this->capacity = capacity;
	this->front = 0;
	this->rear = 0;
}

bool	queue_is_empty(t_queue *this)
{
	return (this->count == 0);
}

bool	queue_is_full(t_queue *this)
{
	return (this->count == this->capacity);
}

void	queue_enqueue(t_queue *this, void *elem)
{
	if (this->count == this->capacity)
		queue_resize(this, this->capacity * 2);
	if (this->rear == (this->capacity - 1) * this->type_size)
	{
		ft_memmove(&this->data[0], elem, this->type_size);
		this->rear = 0;
	}
	else
	{
		ft_memmove(&this->data[this->count * this->type_size], \
					elem, this->type_size);
		this->rear += this->type_size;
	}
    this->count++;
}

void	*queue_dequeue(t_queue *this)
{
	uint8_t	*elem;

	if (this->count == 0)
		return (NULL);
	elem = allocate(this->type_size);
	ft_memcpy(elem, this->data[this->front], this->type_size);
	if (this->front == (this->capacity - 1) * this->type_size)
		this->front = 0;
	else
		this->front += this->type_size;
	this->count--;
	return ((void *)elem);
}
