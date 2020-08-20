/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:11:07 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:11:10 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"

t_array		ar_new(size_t type_size)
{
	t_array		new;

	new = (t_array){NULL, 0, 0, type_size};
	ar_reserve(&new, 1);
	return (new);
}
