
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "libds.h"

static
int32_t	index_of_key(t_map *this, const char *key)
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

int	map_init(t_map *this, size_t type_size, size_t capacity)
{
	if (list_init(&this->key, sizeof(char *), capacity) == -1)
		return (-1);
	if (list_init(&this->value, type_size, capacity) == -1)
		return (list_free(&this->key), -1);
	return (0);
}

int	map_put(t_map *this, const char *key, void *data)
{
	int32_t	entry_idx;

	entry_idx = index_of_key(this, key);
	if (entry_idx != -1)
		if (list_set(&this->value, entry_idx, data) == -1)
			return (-1);
	if (list_push(&this->key, &(char *){ft_strdup(key)}) == -1
		|| list_push(&this->value, data) == -1)
		return (-1);
	return (0);
}

int	map_get(t_map *this, const char *key, void *out)
{
	int32_t	entry_idx;

	entry_idx = index_of_key(this, key);
	if (entry_idx == -1)
		return (-1);
	if (list_get(&this->value, entry_idx, out) == -1)
		return (-1);
	return (0);
}

void	map_free(t_map *this)
{
	list_free(&this->key);
	list_free(&this->value);
}
