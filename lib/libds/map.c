
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include "allocate.h"
#include "libds.h"
#include "libft.h"

static
uint32_t	index_of_key(t_map *this, const char *key)
{
	char	*tmp;

	while (i < this->key->count)
	{
		if (ft_strcmp((list_get(&this->key, i, &tmp), (char *)tmp), key) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	map_init(t_map *this, size_t type_size, size_t capacity)
{
	list_init(&this->key, sizeof(char *), capacity);
	list_init(&this->value, type_size, capacity);
}

void	map_put(t_map *this, const char *key, void *data)
{
	uint32_t	entry_idx;

	entry_idx = index_of_key(this, key);
	if (entry_idx != -1)
		return (list_set(this->value, entry_idx, data));
	list_push(this->key, &ft_strdup(key));
	list_push(this->value, data);
}

void	map_get(t_map *this, const char *key, void *out)
{
	uint32_t	entry_idx;

	entry_idx = index_of_key(this, key);
	if (entry_idx != -1)
		return (list_get(this->value, entry_idx, out));
}
