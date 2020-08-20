/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:17:03 by scoron            #+#    #+#             */
/*   Updated: 2020/06/23 14:04:52 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_int32		cw_sum(t_uint32 arg1, t_uint32 arg2)
{
	return (t_int32)((t_int64)arg1 + (t_int64)arg2);
}

t_int32		cw_minus(t_uint32 arg1, t_uint32 arg2)
{
	return (t_int32)((t_int64)arg1 - (t_int64)arg2);
}

t_int32		cw_and(t_cw_proc *proc, t_uint8 *pos)
{
	t_uint8		*cursor;
	t_uint32	arg[2];
	t_uint8		rg;

	cursor = cw_jump(pos, 2, 0);
	arg[0] = cw_get_arg(proc, &cursor, 0, A_LDIR | A_SIND | A_VAL);
	arg[1] = cw_get_arg(proc, &cursor, 1, A_LDIR | A_SIND | A_VAL);
	rg = (t_uint8)cw_get_arg(proc, &cursor, 2, A_REG);
	proc->pos = cw_jump(proc->pos, (t_int32)(cursor - proc->pos), 42);
	if (rg < 0x1 || rg > REG_NUMBER || cw_check_regs_valid(pos, 0xfc, 0))
		return (FAILED);
	proc->reg[rg] = arg[0] & arg[1];
	if (g_cwdata.verbose == 1)
		ft_printf("and : copying 0x%x & 0x%x = 0x%x to r%d\n",
				arg[0], arg[1], arg[0] & arg[1], rg);
	cw_carry(proc, proc->reg[rg]);
	return (SUCCESS);
}
