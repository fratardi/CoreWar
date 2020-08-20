/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:10:29 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:10:38 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_array.h"
#include "libft.h"

t_array		*ar_alloc(size_t type_size)
{
	t_array	*new;

	if (!(new = (t_array *)malloc(sizeof(t_array))))
		return (NULL);
	ft_bzero(new, sizeof(t_array));
	new->type_size = type_size;
	return (ar_reserve(new, 1) ? NULL : new);
}
