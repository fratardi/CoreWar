/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpacaud <tpacaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:02:14 by tpacaud           #+#    #+#             */
/*   Updated: 2020/06/19 15:37:18 by tpacaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <unistd.h>

size_t		cw_btoi(const t_uint8 *m, size_t len)
{
	size_t		total;

	total = 0;
	while (len)
		total += (t_int32)*m++ * ft_power(16, (t_int32)(--len * 2));
	return (total);
}

void		cw_carry(t_cw_proc *proc, t_int32 off)
{
	if (off)
		proc->carry = 0;
	else
		proc->carry = 1;
}

t_int32		abs(t_int32 nb)
{
	return (nb < 0 ? -nb : nb);
}

t_uint32	convert_magic(t_uint32 d)
{
	return ((d & 0x000000ff) << 24
			| (d & 0x0000ff00) << 8
			| (d & 0x00ff0000) >> 8
			| (d & 0xff000000) >> 24);
}
