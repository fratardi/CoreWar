/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:17:03 by scoron            #+#    #+#             */
/*   Updated: 2020/06/23 14:04:52 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_int32		cw_aff(t_cw_proc *proc, t_uint8 *pos)
{
	t_uint8 c;

	pos = cw_jump(pos, 1, 0);
	if (*pos >= 0x1 && *pos <= MAX_OP)
	{
		c = (char)(proc->reg[*pos] % 256);
		if (g_cwdata.verbose == 1)
			ft_printf("aff by %s : value of r%d is \"%c\"\n",
			proc->champ->name, *pos, c);
		proc->pos = cw_jump(proc->pos, 3, 42);
	}
	else
	{
		proc->pos = cw_jump(proc->pos,
				error_jump(proc->pos, proc->opc), 42);
		return (FAILED);
	}
	return (SUCCESS);
}
