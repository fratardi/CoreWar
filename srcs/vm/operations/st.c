/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:17:03 by scoron            #+#    #+#             */
/*   Updated: 2020/06/23 14:04:52 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_int32	streg(t_cw_proc *proc,
		t_uint8 *pos, t_uint8 *cursor)
{
	t_int32	dest;
	t_int32	v;

	v = cw_get_arg(proc, &cursor, 0, A_VAL);
	dest = cw_get_arg(proc, &cursor, 1, A_REG);
	proc->pos = cw_jump(proc->pos, (t_int32)(cursor - proc->pos), 42);
	if (dest < 0x1 || dest > REG_NUMBER ||
		cw_check_regs_valid(pos, 0xf0, 0))
		return (FAILED);
	if (g_cwdata.verbose == 1)
		ft_printf("st : copying value 0x%x at r%d\n", v, dest);
	proc->reg[dest] = v;
	return (SUCCESS);
}

static t_int32	stind(t_cw_proc *proc,
		t_uint8 *pos, t_uint8 *cursor)
{
	t_int32	dest;
	t_int32	v;
	t_uint8	*loc;

	v = cw_get_arg(proc, &cursor, 0, A_VAL);
	v = convert_magic((t_uint32)v);
	dest = cw_read(cursor, 2);
	cursor = cw_jump(cursor, 2, 0);
	if (cw_check_regs_valid(pos, 0xc0, 0))
	{
		proc->pos = cw_jump(proc->pos, (t_int32)(cursor - proc->pos), 42);
		return (FAILED);
	}
	if (g_cwdata.verbose == 1)
		ft_printf("st : copying value 0x%x at addr "
			"distant of 0x%.4x\n", v, dest);
	loc = cw_jump(pos, dest, 1);
	cw_write_int(loc, (t_uint8 *)&v, proc->nb);
	proc->pos = cw_jump(proc->pos, (t_int32)(cursor - proc->pos), 42);
	return (SUCCESS);
}

t_int32			cw_st(t_cw_proc *proc, t_uint8 *pos)
{
	t_uint8 *cursor;
	t_uint8 *arg_code;

	cursor = cw_jump(pos, 2, 0);
	arg_code = cw_jump(pos, 1, 0);
	if ((*arg_code & g_argcode[1].mask) >> g_argcode[1].shift == REG_CODE)
		return (streg(proc, pos, cursor));
	else if ((*arg_code & g_argcode[1].mask) >> g_argcode[1].shift == IND_CODE)
		return (stind(proc, pos, cursor));
	return (SUCCESS);
}
