/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:17:03 by scoron            #+#    #+#             */
/*   Updated: 2020/06/23 14:04:52 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_int32		cw_lfork(t_cw_proc *proc, t_uint8 *pos)
{
	t_cw_proc	fork;
	t_uint8		*cursor;
	t_int32		loc;

	cursor = cw_jump(pos, 1, 0);
	loc = cw_read(cursor, 2);
	fork_proc(&fork, proc, cw_jump(pos, loc, 0));
	fork_push_proc(&fork);
	proc->pos = cw_jump(pos, 3, 42);
	if (g_cwdata.verbose == 1)
		ft_printf("lfork : forked process of champ [%s] at addr "
			"0x%.4x with id %d\n", fork.champ->name,
			fork.pos - g_cwdata.memory, g_cwdata.first_proc->nb);
	return (SUCCESS);
}
