/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:17:03 by scoron            #+#    #+#             */
/*   Updated: 2020/06/23 14:04:52 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_int32		cw_zjmp(t_cw_proc *proc, t_uint8 *pos)
{
	t_uint8	*cursor;
	t_int16	loc;

	cursor = cw_jump(pos, 1, 0);
	loc = (t_int16)cw_read(cursor, sizeof(t_int16));
	if (proc->carry)
	{
		proc->pos = cw_jump(proc->pos, loc, 1);
		if (g_cwdata.verbose == 1)
			ft_printf("zjmp : carry positive, jumping by %d bytes to "
			"0x%.4x\n", loc, proc->pos - g_cwdata.memory);
	}
	else
	{
		proc->pos = cw_jump(proc->pos, 3, 2);
		if (g_cwdata.verbose == 1)
			ft_printf("zjmp : carry negative, jumping by 3 bytes to "
			"0x%.4x\n", proc->pos - g_cwdata.memory);
	}
	proc->step = S_RUNNING;
	return (SUCCESS);
}
