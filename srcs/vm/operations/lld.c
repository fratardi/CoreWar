/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:17:03 by scoron            #+#    #+#             */
/*   Updated: 2020/06/23 14:04:52 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_int32		cw_lld(t_cw_proc *proc, t_uint8 *pos)
{
	t_uint8	*cursor;
	t_int32	val;
	t_int32	rg;

	cursor = cw_jump(pos, 2, 0);
	val = cw_get_arg(proc, &cursor, 0, A_IND | A_LDIR);
	rg = cw_get_arg(proc, &cursor, 1, A_REG);
	proc->pos = cw_jump(proc->pos, (t_int32)(cursor - proc->pos), 42);
	if (rg < 0x1 || rg > REG_NUMBER || cw_check_regs_valid(pos, 0xf0, 0))
		return (FAILED);
	if (g_cwdata.verbose == 1)
		ft_printf("lld : copying value 0x%x in r%d\n", val, val, rg);
	proc->reg[rg] = val;
	cw_carry(proc, val);
	return (SUCCESS);
}
