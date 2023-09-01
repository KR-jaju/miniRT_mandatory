#ifndef LIBDS_H
#define LIBDS_H

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>
# include "libft.h"

/* -------------------------- STRUCT DECLARATIONS --------------------------- */

typedef struct s_stack
{
	uint8_t		*data;
	size_t		type_size;
	int			count;
	int			capacity;
	size_t		top;
}t_stack;

typedef struct s_queue
{
	uint8_t		*data;
	size_t		type_size;
	int			count;
	int			capacity;
	size_t		front;
	size_t		rear;
}t_queue;

typedef struct s_list
{
	void		*data;
	size_t		type_size;
	uint32_t	count;
	uint32_t	capacity;
}t_list;

typedef struct s_map
{
	t_list		key;
	t_list		value;
}t_map;

/* -------------------------- FUNCTION PROTOTYPES --------------------------- */

// stack
void	stack_init(t_stack *this, size_t type_size, size_t capacity);
void	stack_resize(t_stack *this, size_t new_size);
bool	stack_is_empty(t_stack *this);
bool	stack_is_full(t_stack *this);
void	stack_push(t_stack *this, void *elem);
void	*stack_pop(t_stack *this);
void	*stack_peek(t_stack *this);

// queue
void	queue_init(t_queue *this, size_t type_size, size_t capacity);
void	queue_resize(t_queue *this, size_t new_size);
bool	queue_is_empty(t_queue *this);
bool	queue_is_full(t_queue *this);
void	queue_enqueue(t_queue *this, void *elem);
void	*queue_dequeue(t_queue *this);

// list
void	list_init(t_list *this, size_t type_size, size_t capacity);
void	list_push(t_list *this, void *data);
void	list_set(t_list *this, uint32_t idx, void *data);
void	list_get(t_list *this, uint32_t idx, void *out);
void	*list_collect(t_list *this, uint32_t *len);

// map
void	map_init(t_map *this, size_t type_size, size_t capacity);
void	map_put(t_map *this, const char *key, void *data);
void	map_get(t_map *this, const char *key, void *out);

#endif
