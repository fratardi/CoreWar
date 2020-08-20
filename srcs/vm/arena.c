/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpacaud <tpacaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:24:26 by tpacaud           #+#    #+#             */
/*   Updated: 2020/06/14 11:57:28 by tpacaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <unistd.h>

void	fill_champ_arena(t_uint8 *pos, t_champ *champ, t_uint32 color)
{
	size_t		size;
	t_uint32	i;
	t_uint32	k;

	size = champ->exec_size;
	i = 0;
	while (i < size)
	{
		k = pos - g_cwdata.memory;
		k %= MEM_SIZE;
		g_cwdata.memory[k] = champ->exec[i];
		g_cwdata.colors[k] = color;
		pos = cw_jump(pos, 1, 0);
		i++;
	}
}

void	init_process(t_cw_proc *proc, t_champ *champ, t_uint32 color)
{
	ft_bzero(proc, sizeof(t_cw_proc));
	proc->champ = champ;
	proc->pos = g_cwdata.memory + ((abs(champ->nb) - 1)
		* (MEM_SIZE / g_cwdata.nbr_champ));
	proc->reg[1] = champ->nb;
	proc->last_live = 0;
	proc->carry = 0;
	proc->step = S_RUNNING;
	proc->next = NULL;
	proc->opc = 0;
	fill_champ_arena(proc->pos, champ, color);
}

void	push_proc(t_cw_proc *proc)
{
	t_cw_proc *tmp;

	proc = ft_memcpy(ft_memalloc(sizeof(t_cw_proc)), proc, sizeof(t_cw_proc));
	if (g_cwdata.first_proc == NULL)
	{
		proc->nb = g_cwdata.nbr_champ;
		g_cwdata.first_proc = proc;
	}
	else
	{
		tmp = g_cwdata.first_proc;
		while (tmp->next)
			tmp = tmp->next;
		proc->nb = tmp->nb - 1;
		tmp->next = proc;
	}
	++g_cwdata.nbr_proc;
	++g_cwdata.nbr_histo;
}

t_int32	init_arena(void)
{
	t_cw_proc	proc;
	t_champ		*champ;
	t_uint32	color;

	if (g_cwdata.nbr_champ == 0)
		cw_exit(FAILED, 1, "ERROR : no champions");
	champ = g_cwdata.first_champ;
	print_champions_list(champ);
	clear_color();
	color = g_cwdata.nbr_champ;
	while (champ)
	{
		init_process(&proc, champ, color);
		push_proc(&proc);
		champ = champ->next;
		color--;
	}
	return (SUCCESS);
}
