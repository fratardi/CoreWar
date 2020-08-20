/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dic_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:12:38 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:12:40 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dico.h"

void		*dic_get(t_dico *dico, void *key)
{
	t_entry	*entry;
	size_t	id;

	id = dico->hashing(key, dico->key_size, dico->is_char);
	entry = *(dico->map + id % dico->limit);
	while (entry)
	{
		if (id == entry->id && \
				!dico->key_cmp(&key, &entry->key, dico->key_size))
			return (entry->value);
		entry = entry->next;
	}
	return (NULL);
}
