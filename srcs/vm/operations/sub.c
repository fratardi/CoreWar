/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:17:03 by scoron            #+#    #+#             */
/*   Updated: 2020/06/23 14:04:52 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_int32		cw_sub(t_cw_proc *proc, t_uint8 *pos)
{
	t_uint8	*cursor;
	t_int32	arg[3];

	cursor = cw_jump(pos, 2, 0);
	arg[0] = cw_get_arg(proc, &cursor, 0, A_VAL | A_IND);
	arg[1] = cw_get_arg(proc, &cursor, 1, A_VAL | A_IND);
	arg[2] = cw_get_arg(proc, &cursor, 2, A_REG | A_IND);
	proc->pos = cw_jump(proc->pos, (t_int32)(cursor - proc->pos), 42);
	if (arg[2] < 0x1 || arg[2] > REG_NUMBER ||
		cw_check_regs_valid(pos, 0xfc, 0))
		return (FAILED);
	proc->reg[arg[2]] = cw_minus(arg[0], arg[1]);
	if (g_cwdata.verbose == 1)
		ft_printf("sub : copying 0x%x - 0x%x = 0x%x to r%d\n",
				arg[0], arg[1], cw_minus(arg[0], arg[1]));
	cw_carry(proc, proc->reg[arg[2]]);
	return (SUCCESS);
}
