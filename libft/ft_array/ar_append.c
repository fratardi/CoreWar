/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:10:43 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:10:50 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"
#include "libft.h"

int		ar_append(t_array *arr, void const *data, size_t datalen)
{
	if (ar_reserve(arr, datalen))
		return (1);
	ft_memcpy(ar_end(arr), &data, ar_offset(arr, datalen));
	arr->size += datalen;
	return (0);
}

int		ar_append_free(t_array *arr, void *data, size_t datalen)
{
	ar_append(arr, data, datalen);
	free(data);
	return (0);
}

int		ar_insert(
		t_array *self, void const *data, size_t datalen, size_t index)
{
	if (self->size < index || ar_reserve(self, datalen))
		return (1);
	ft_memmove(ar_get(self, index + datalen),
			ar_get(self, index), ar_offset(self, self->size - index));
	ft_memcpy(ar_get(self, index), &data, ar_offset(self, datalen));
	self->size += datalen;
	return (0);
}

int		ar_append_char(t_array *arr, char data)
{
	if (ar_reserve(arr, 1))
		return (1);
	ft_memcpy(ar_end(arr), &data, ar_offset(arr, 1));
	arr->size += 1;
	return (0);
}
