#include "libds.h"

static int	queue_resize(t_queue *this, int new_capacity)
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

int	queue_init(t_queue *this, size_t type_size, int capacity)
{
	this->data = malloc(type_size * capacity);
	if (!this->data)
		return (-1);
	this->type_size = type_size;
	this->count = 0;
	this->capacity = capacity;
	this->front = 0;
	this->rear = 0;
	return (0);
}

bool	queue_is_empty(t_queue *this)
{
	return (this->count == 0);
}

bool	queue_is_full(t_queue *this)
{
	return (this->count == this->capacity);
}

int	queue_enqueue(t_queue *this, void *elem)
{
	if (this->count == this->capacity \
		|| queue_resize(this, this->capacity * 2) == -1)
		return (-1);
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
	return (0);
}

void	*queue_dequeue(t_queue *this)
{
	uint8_t	*elem;

	if (this->count == 0)
		return (NULL);
	elem = malloc(this->type_size);
	if (!elem)
		return (NULL);
	ft_memcpy(elem, &this->data[this->front], this->type_size);
	if (this->front == (this->capacity - 1) * this->type_size)
		this->front = 0;
	else
		this->front += this->type_size;
	this->count--;
	return ((void *)elem);
}
