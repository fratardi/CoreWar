/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dic_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:12:25 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:12:32 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dico.h"

static size_t		hashing(const void *id, size_t size, int is_char)
{
	size_t			id_hashed;
	unsigned char	*pts;

	id_hashed = 0;
	pts = (unsigned char *)id;
	if (is_char)
		size = ft_strlen((char *)id);
	while (size--)
	{
		id_hashed += *(pts++);
		id_hashed += (id_hashed << 10);
		id_hashed ^= (id_hashed >> 6);
	}
	id_hashed += (id_hashed << 3);
	id_hashed ^= (id_hashed >> 11);
	return (id_hashed + (id_hashed << 15));
}

t_dico				*dic_alloc(size_t nb_entries)
{
	t_dico	*dico;

	if (!nb_entries)
		nb_entries = DICO_MIN_SIZE;
	dico = (t_dico *)ft_memalloc(sizeof(t_dico));
	dico->map = (t_entry **)\
		ft_memalloc(sizeof(t_entry *) * (nb_entries + 1));
	dico->limit = nb_entries;
	dico->hashing = hashing;
	dico->key_cpy = ft_memcpy;
	dico->key_cmp = ft_memcmp;
	dico->value_cmp = ft_memcmp;
	dico->value_cpy = ft_memcpy;
	dico->key_size = sizeof(void *);
	dico->value_size = sizeof(void *);
	return (dico);
}
