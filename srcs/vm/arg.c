/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpacaud <tpacaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:02:14 by tpacaud           #+#    #+#             */
/*   Updated: 2020/06/19 15:37:18 by tpacaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_argcode		g_argcode[MAX_ARGS_NUMBER + 1] =
{
	{0xc0, 6},
	{0x30, 4},
	{0x0c, 2},
	{0x03, 0},
};

t_uint8			*cp_on_buf(t_uint8 *buf, t_uint8 *pos, t_uint16 nb)
{
	t_uint8	i;

	ft_memset(buf, '\0', nb * sizeof(t_uint8));
	i = 0;
	while (i < nb)
	{
		buf[i++] = *pos;
		pos = cw_jump(pos, 1, 0);
	}
	return (buf);
}

t_int32			cw_read(t_uint8 *cursor, t_uint16 nb)
{
	t_uint8	buf[nb + 1];

	if (nb == sizeof(t_uint16))
		return ((t_int32)(t_int16)cw_btoi(cp_on_buf(buf, cursor, nb), nb));
	return ((t_int32)cw_btoi(cp_on_buf(buf, cursor, nb), nb));
}

static t_int32	go_to_arg(t_uint8 **cursor, t_uint8 *pos, t_uint32 code_type)
{
	t_uint8		*tmp;
	t_uint16	length;
	t_uint16	jump;

	length = sizeof(t_uint16);
	jump = length;
	if (code_type & A_DIR || code_type & A_LDIR)
	{
		tmp = *cursor;
		length = (t_uint16)((code_type & A_LDIR) ?
							sizeof(t_int32) : sizeof(t_uint16));
		jump = length;
	}
	else if ((code_type & A_IND) || (code_type & A_SIND))
	{
		tmp = cw_jump(pos, cw_read(*cursor, jump), code_type & A_SIND);
		length = sizeof(t_int32);
	}
	else
		return (0);
	*cursor = cw_jump(*cursor, jump, 0);
	return (cw_read(tmp, length));
}

t_int32			cw_get_arg(t_cw_proc *proc, t_uint8 **cursor,
						t_uint8 nb, t_uint32 code_type)
{
	t_uint8	param;
	t_int32	arg;
	t_uint8	reg;

	param = (*cw_jump(proc->pos, 1, 0) &
			g_argcode[nb].mask) >> g_argcode[nb].shift;
	arg = 0;
	if (param == REG_CODE)
	{
		reg = (t_uint8)**cursor;
		if (reg <= REG_NUMBER && reg >= 0x1)
			arg = (code_type & A_VAL) ? proc->reg[reg] : reg;
		*cursor = cw_jump(*cursor, 1, 0);
	}
	else if (param == DIR_CODE)
		arg = go_to_arg(cursor, proc->pos, (code_type & A_DIR) |
		(code_type & A_LDIR));
	else if (param == IND_CODE)
		arg = go_to_arg(cursor, proc->pos, (code_type & A_IND) |
		(code_type & A_SIND));
	return (arg);
}
