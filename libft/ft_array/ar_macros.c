/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_macros.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 18:10:20 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 18:10:22 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"

size_t		ar_offset(t_array *a, size_t i)
{
	return (i * a->type_size);
}

void		*ar_get(t_array *a, size_t i)
{
	return (a->data + ar_offset(a, i));
}

void		*ar_end(t_array *a)
{
	return (a->data + ar_offset(a, a->size));
}
