/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpacaud <tpacaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 14:50:44 by tpacaud           #+#    #+#             */
/*   Updated: 2019/06/20 18:17:28 by tpacaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**Size of octal and Hexa
*/

size_t	ft_size_octal(unsigned long long int to_convert)
{
	size_t ret;

	ret = 0;
	while (to_convert)
	{
		to_convert = to_convert / 8;
		ret++;
	}
	return (ret);
}

size_t	ft_size_hexa(unsigned long long int to_convert)
{
	size_t ret;

	ret = 0;
	while (to_convert)
	{
		to_convert = to_convert / 16;
		ret++;
	}
	return ((ret != 0) ? ret-- : 0);
}
