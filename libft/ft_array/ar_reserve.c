/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_reserve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:11:21 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:11:25 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"

int		ar_reserve(t_array *arr, size_t reserve_sup)
{
	const size_t	total_size = reserve_sup + arr->size;
	size_t			new_size;

	if (total_size > arr->limit)
	{
		new_size = (arr->limit > 0 ? arr->limit : ARR_MIN_SIZE);
		while (new_size < total_size)
			new_size *= ARR_FACTOR;
		return (ar_resize(arr, new_size));
	}
	return (0);
}
