/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpacaud <tpacaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:02:14 by tpacaud           #+#    #+#             */
/*   Updated: 2020/06/19 15:37:18 by tpacaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char			get_arg_type_disasm(t_uint32 arg)
{
	if (arg == REG_CODE)
		return ('r');
	if (arg == DIR_CODE)
		return (DIRECT_CHAR);
	if (arg == IND_CODE)
		return (1);
	return (0);
}

void			print_data(void)
{
	ft_printf("\033[33m--------------- DATA ---------------\033[00m\n\n");
	ft_printf("Currently at cycle number : %d\n", g_cwdata.nbr_cycle);
	ft_printf("Cycles To Die : %d\n", g_cwdata.cycles_to_die);
	ft_printf("Number of cycles since last check : %d\n",
			g_cwdata.since_last_check);
	ft_printf("Next check coming at cycle : %d\n", g_cwdata.nbr_cycle
			+ g_cwdata.cycles_to_die - g_cwdata.since_last_check);
	ft_printf("Number of checks : %u\n", g_cwdata.checks);
	ft_printf("Lives Count : %u\n", g_cwdata.lives_count);
	ft_printf("Champions Alive : %u\n", g_cwdata.nbr_champ);
	ft_printf("Number of Processes alive: %u\n", g_cwdata.nbr_proc);
	ft_printf("\n");
}

static void		print_infos(t_cw_proc *proc)
{
	ft_printf("Carriage Unique Number, %zu\n", proc->nb);
	ft_printf("Associated Champion, %s (%d)\n", proc->champ->name,
			-proc->champ->nb);
	ft_printf("OP Code, %zu - 0x%x\n", *proc->pos, *proc->pos);
	ft_printf("Cycles Left, %zu\n", proc->cycles_left);
	ft_printf("Position, %zu = 0x%.4x\n", proc->pos - g_cwdata.memory,
			proc->pos - g_cwdata.memory);
	ft_printf("Last say live, %zu\n", proc->last_live);
	ft_printf("Carry value, %zu\n\n", proc->carry);
}

void			print_carriage(void)
{
	t_cw_proc	*process;
	t_int32		r;

	process = g_cwdata.first_proc;
	print_data();
	ft_printf("\033[33m--------------- PROCESSES LIST "
			"---------------\033[00m\n\n");
	while (process)
	{
		print_infos(process);
		r = -1;
		while (++r < REG_NUMBER)
			ft_printf("Register %d = 0x%x (equal to %d)\n", r,
					process->reg[r], process->reg[r]);
		ft_printf("\n");
		process = process->next;
	}
}
