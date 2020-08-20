/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_popindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:11:15 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:11:18 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"
#include "libft.h"

int	ar_popindex(t_array *arr, size_t index, size_t len)
{
	size_t	n;

	n = len > arr->size - index ? arr->size - index : len;
	if (index > arr->size)
		return (1);
	ft_memmove(ar_get(arr, index), ar_get(arr, index + n),
			ar_offset(arr, arr->size - n - index));
	arr->size -= n;
	return (0);
}
