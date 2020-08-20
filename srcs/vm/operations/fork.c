/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:17:03 by scoron            #+#    #+#             */
/*   Updated: 2020/06/23 14:04:52 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fork_proc(t_cw_proc *new_proc, t_cw_proc *src, t_uint8 *pos)
{
	ft_memcpy(new_proc, src, sizeof(t_cw_proc));
	new_proc->pos = pos;
	new_proc->step = S_RUNNING;
}

void	fork_push_proc(t_cw_proc *proc)
{
	proc = ft_memcpy(ft_memalloc(sizeof(t_cw_proc)), proc, sizeof(t_cw_proc));
	proc->nb = g_cwdata.nbr_histo + 1;
	proc->next = g_cwdata.first_proc;
	g_cwdata.first_proc = proc;
	++g_cwdata.nbr_proc;
	++g_cwdata.nbr_histo;
}

t_int32	cw_fork(t_cw_proc *proc, t_uint8 *pos)
{
	t_cw_proc	fork;
	t_uint8		*cursor;
	t_int32		loc;

	cursor = cw_jump(pos, 1, 0);
	loc = cw_read(cursor, 2);
	fork_proc(&fork, proc, cw_jump(pos, loc, 1));
	fork_push_proc(&fork);
	if (g_cwdata.verbose == 1)
		ft_printf("fork : forked process of champ [%s] at addr 0x%.4x"
			" (%+d) with id %d\n", fork.champ->name, fork.pos - g_cwdata.memory,
			loc, g_cwdata.first_proc->nb);
	proc->pos = cw_jump(pos, 3, 42);
	return (SUCCESS);
}
