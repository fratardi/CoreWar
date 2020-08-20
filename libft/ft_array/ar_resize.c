/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_resize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:11:59 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:12:03 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"
#include "libft.h"

int		ar_resize(t_array *arr, size_t new_size)
{
	void	*res;

	res = malloc(new_size * arr->type_size);
	if (res == NULL)
		return (1);
	if (arr->size > new_size)
		arr->size = new_size;
	ft_memcpy(res, arr->data, arr->size * arr->type_size);
	free(arr->data);
	arr->data = res;
	arr->limit = new_size;
	return (0);
}
