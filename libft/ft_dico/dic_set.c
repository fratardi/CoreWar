/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dic_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:12:41 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:12:46 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dico.h"
#include <stdlib.h>

static void		move_entry(t_entry **new_map, t_entry *loc, size_t limit)
{
	t_entry	**addr;
	t_entry	*next;

	while (loc)
	{
		next = loc->next;
		addr = new_map + loc->id % limit;
		loc->next = *addr;
		*addr = loc;
		loc = next;
	}
}

static void		resize(t_dico *dico)
{
	t_entry	**resized_map;
	t_entry	**map;
	size_t	old_size;

	old_size = dico->limit;
	if (old_size < (2147483647 / DICO_FACTOR))
		dico->limit = old_size * DICO_FACTOR;
	resized_map = (t_entry **)\
		ft_memalloc(sizeof(t_entry *) * dico->limit);
	map = dico->map;
	while (old_size--)
	{
		if (*map)
			move_entry(resized_map, *map, dico->limit);
		map++;
	}
	free(dico->map);
	dico->map = resized_map;
}

static void		add_entry(t_dico *dico, void *key, void *value)
{
	size_t	id;
	t_entry **map_loc;
	t_entry	*tmp;

	id = dico->hashing(key, dico->key_size, dico->is_char);
	map_loc = dico->map + id % dico->limit;
	tmp = *map_loc;
	while (tmp)
	{
		if (id == tmp->id && !dico->key_cmp(&key, &tmp->key, dico->key_size))
		{
			dico->key_del ? dico->key_del(key, dico->key_size) : 0;
			dico->value_del ? dico->value_del(tmp->value, dico->value_size) : 0;
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	tmp = (t_entry *)ft_memalloc(sizeof(t_entry));
	dico->key_cpy(&tmp->key, &key, dico->key_size);
	dico->value_cpy(&tmp->value, &value, dico->value_size);
	tmp->id = id;
	tmp->next = *map_loc;
	*map_loc = tmp;
}

void			dic_set(t_dico *dico, void *key, void *value)
{
	add_entry(dico, key, value);
	dico->size++;
	if (dico->size / dico->limit > DICO_RESIZE_LIMIT)
		resize(dico);
}
