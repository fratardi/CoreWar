/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dic_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:12:33 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:12:37 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dico.h"

static void		del_one_dic(t_dico *dico, t_entry *entry)
{
	t_entry	*next;

	while (entry)
	{
		next = entry->next;
		if (dico->value_del)
			dico->value_del(entry->value, dico->value_size);
		if (dico->key_del)
			dico->key_del(entry->key, dico->key_size);
		ft_memdel((void *)&entry);
		entry = next;
	}
}

void			dic_del(t_dico **dico)
{
	t_entry	**map;

	map = (*dico)->map;
	while ((*dico)->limit--)
	{
		if (*map)
			del_one_dic(*dico, *map);
		map++;
	}
	ft_memdel((void *)&(*dico)->map);
	ft_memdel((void *)dico);
}
