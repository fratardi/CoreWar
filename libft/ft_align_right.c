/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_align_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 18:05:50 by scoron            #+#    #+#             */
/*   Updated: 2019/01/19 15:49:45 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_align_right(char *str)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	if (len == 0)
		return ;
	while (len > i && str[len - 1 - i] == ' ')
		i++;
	while (--len - i >= 0)
		str[len] = str[len - i];
	while (--i >= 0)
		str[i] = ' ';
}
