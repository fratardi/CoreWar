/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratardi <fratardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:02:14 by fratardi          #+#    #+#             */
/*   Updated: 2020/07/01 17:47:32 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui/vm.h"
#include <stdlib.h>

void		cw_dump(void)
{
	t_int32	line_count;
	t_int32	char_count;
	t_int32	line_nb;
	t_uint8 color;
	t_uint8	*memory;

	line_count = -1;
	line_nb = -0x40;
	memory = &g_cwdata.memory[0];
	g_cwdata.verbose == 2 ? print_carriage() : 0;
	while (++line_count < MEM_SIZE / 64)
	{
		char_count = -1;
		ft_printf("0x%.4x : ", line_nb += 0x40);
		while (++char_count < 64)
			if (g_cwdata.verbose > 0)
			{
				color = g_cwdata.colors[line_count * 64 + char_count];
				color = color == 0 ? 0 : 30 + color;
				ft_printf("\033[%dm%.2x \033[0m", color, *memory++);
			}
			else
				ft_printf("%.2x ", *memory++);
		ft_printf("\n");
	}
}

void		print_winner(void)
{
	t_champ	*champs;
	t_champ	*chosen_one;

	champs = g_cwdata.first_champ;
	chosen_one = champs;
	ft_printf("\n");
	while (chosen_one && champs != NULL)
	{
		if (g_cwdata.verbose == 1)
			ft_printf("champs %s last live was at cycle : %d\n",
				champs->name, champs->last_live);
		if (champs->last_live >= chosen_one->last_live)
			chosen_one = champs;
		champs = champs->next;
	}
	if (chosen_one)
		ft_printf("\033[31m !!! ET LE GRAND GAGNANT DE CE TOURNOIS DE "
			"CHAMPIONS EST %s(%d) !!!\n Number of cycles was : %d\033[00m\n",
			chosen_one->name, (-1 * chosen_one->nb), g_cwdata.nbr_cycle);
}

void		del_proc(t_cw_proc *dead_proc)
{
	t_cw_proc *current;
	t_cw_proc *tmp;

	--g_cwdata.nbr_proc;
	current = g_cwdata.first_proc;
	tmp = NULL;
	if (g_cwdata.verbose == 1)
		ft_printf("\nCycle %d : Process number %d (associated to %s (%d)) "
			"worthless life has ended\n", g_cwdata.nbr_cycle,
			dead_proc->nb, dead_proc->champ->name, dead_proc->champ->nb);
	while (current)
		if (current == dead_proc)
		{
			if (tmp == NULL)
				g_cwdata.first_proc = dead_proc->next;
			else
				tmp->next = dead_proc->next;
			free(dead_proc);
			return ;
		}
		else
		{
			tmp = current;
			current = current->next;
		}
}

static void	dying_cycle(void)
{
	t_cw_proc *current;
	t_cw_proc *next;

	g_cwdata.since_last_check = 0;
	current = g_cwdata.first_proc;
	while (current)
	{
		current->champ->lives_count = 0;
		next = current->next;
		if (g_cwdata.nbr_cycle - current->last_live >= g_cwdata.cycles_to_die)
			del_proc(current);
		current = next;
	}
	if (g_cwdata.lives_count >= NBR_LIVE || ++g_cwdata.checks == MAX_CHECKS)
	{
		g_cwdata.cycles_to_die -= CYCLE_DELTA;
		g_cwdata.checks = 0;
	}
	if (g_cwdata.verbose == 1)
		ft_printf("Cycle %d : Dying cycle has passed, cycle_to_die = %d\n",
				g_cwdata.nbr_cycle, g_cwdata.cycles_to_die);
	g_cwdata.lives_count = 0;
}

void		cw_run(void)
{
	t_cw_proc		*current;
	t_cw_proc		*next;

	while (g_cwdata.cycles_to_die > 0 && g_cwdata.nbr_proc)
	{
		current = g_cwdata.first_proc;
		++g_cwdata.since_last_check;
		++g_cwdata.nbr_cycle;
		while (g_cwdata.nbr_proc && current)
		{
			next = current->next;
			exec_process(current);
			current = next;
		}
		if (g_cwdata.dump > 0 && g_cwdata.nbr_cycle == g_cwdata.dump)
			return (cw_dump());
		g_cwdata.since_last_check >= g_cwdata.cycles_to_die ? dying_cycle() : 0;
	}
	print_winner();
}
