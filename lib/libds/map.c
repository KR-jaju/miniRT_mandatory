
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "libds.h"
#include "libft.h"

static
uint32_t	index_of_key(t_map *this, const char *key)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (i < this->key.count)
	{
		if (ft_strcmp((list_get(&this->key, i, &tmp), (char *)tmp), key) == 0)
			return (i);
		i++;
	}
	return (-1);
}

bool	map_init(t_map *this, size_t type_size, size_t capacity)
{
	if (!list_init(&this->key, sizeof(char *), capacity))
		return (false);
	if (!list_init(&this->value, type_size, capacity))
		return (false);
	return (true);
}

bool	map_put(t_map *this, const char *key, void *data)
{
	uint32_t	entry_idx;

	entry_idx = index_of_key(this, key);
	if (entry_idx != -1)
		if (!list_set(&this->value, entry_idx, data))
			return (true);
	if (!list_push(&this->key, &(char *){ft_strdup(key)})
		|| !list_push(&this->value, data))
		return (false);
	return (true);
}

bool	map_get(t_map *this, const char *key, void *out)
{
	uint32_t	entry_idx;

	entry_idx = index_of_key(this, key);
	if (entry_idx == 1)
		return (false);
	list_get(&this->value, entry_idx, out);
	return (true);
}
