/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:17:03 by scoron            #+#    #+#             */
/*   Updated: 2020/06/23 14:04:52 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
 ** Check one register to be in the right range
*/

t_int32		cw_check_one_reg(t_uint8 **pos,
		t_uint8 pcode, t_uint8 dsize)
{
	if (pcode == REG_CODE && (**pos < 0x1 || **pos > REG_NUMBER))
		return (FAILED);
	*pos = cw_jump(*pos, cw_size_param(pcode, dsize), 0);
	return (SUCCESS);
}

/*
 ** Check if registers args are in the right range
*/

t_int32		cw_check_regs_valid(t_uint8 *pos,
		t_uint8 mask, t_uint8 dir_is_short)
{
	t_uint8 pcode;
	t_uint8 dsize;

	dsize = dir_is_short ? 2 : 4;
	pcode = *cw_jump(pos, 1, 0) & mask;
	pos = cw_jump(pos, 2, 0);
	if ((cw_check_one_reg(&pos, (pcode & 0xc0) >> 6, dsize))
	|| (cw_check_one_reg(&pos, ((pcode & 0x30) >> 4), dsize))
	|| (cw_check_one_reg(&pos, ((pcode & 0x0c) >> 2), dsize)))
		return (FAILED);
	return (SUCCESS);
}

t_int32		cw_sti(t_cw_proc *proc, t_uint8 *pos)
{
	t_uint8	*cursor;
	t_uint8	*loc;
	t_int32	arg[2];
	t_int32	v;

	cursor = cw_jump(pos, 2, 0);
	v = cw_get_arg(proc, &cursor, 0, A_VAL);
	arg[0] = cw_get_arg(proc, &cursor, 1, A_SIND | A_DIR | A_VAL);
	arg[1] = cw_get_arg(proc, &cursor, 2, A_DIR | A_VAL);
	if (cw_check_regs_valid(pos, 0xfc, 1))
	{
		proc->pos = cw_jump(proc->pos, (t_int32)(cursor - proc->pos), 42);
		return (FAILED);
	}
	loc = cw_jump(pos, cw_sum(arg[0], arg[1]), 1);
	v = convert_magic((t_uint32)v);
	if (g_cwdata.verbose == 1)
		ft_printf("sti : copying value 0x%x to addr 0x%.4x (0x%.4x + 0x%.4x)\n",
				v, cw_sum(arg[0], arg[1]), arg[0], arg[1]);
	cw_write_int(loc, (t_uint8 *)&v, proc->nb);
	proc->pos = cw_jump(proc->pos, (t_int32)(cursor - proc->pos), 42);
	return (SUCCESS);
}
