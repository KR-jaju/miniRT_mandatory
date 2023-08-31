#ifndef LIBDS_H
# define LIBDS_H

# include <stdint.h>
# include <stddef.h>

typedef struct s_stack
{
	uint8_t		*data;
	size_t		type_size;
	size_t		top;
	uint32_t	count;
	uint32_t	capacity;
}t_stack;

typedef struct s_queue
{
	uint8_t		*data;
	size_t		type_size;
	size_t		front;
	size_t		rear;
	uint32_t	count;
	uint32_t	capacity;
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


void	list_init(t_list *this, size_t type_size, size_t capacity);
void	list_push(t_list *this, void *data);
void	list_set(t_list *this, uint32_t idx, void *data);
void	list_get(t_list *this, uint32_t idx, void *out);
void	*list_collect(t_list *this, uint32_t *len);

void	map_init(t_map *this, size_t type_size, size_t capacity);
void	map_put(t_map *this, const char *key, void *data);
void	map_get(t_map *this, const char *key, void *out);

#endif
