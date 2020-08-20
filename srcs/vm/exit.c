/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpacaud <tpacaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:02:14 by tpacaud           #+#    #+#             */
/*   Updated: 2020/06/19 15:37:18 by tpacaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>

static void		del_champs(void)
{
	t_champ		*champ;
	void		*tmp;

	champ = g_cwdata.first_champ;
	while (champ)
	{
		tmp = champ->next;
		free(champ);
		champ = (t_champ *)tmp;
	}
	g_cwdata.nbr_champ = 0;
	g_cwdata.first_champ = NULL;
}

static void		del_procs(void)
{
	t_cw_proc	*proc;
	void		*tmp;

	proc = g_cwdata.first_proc;
	while (proc)
	{
		tmp = proc->next;
		free(proc);
		proc = (t_cw_proc *)tmp;
	}
	g_cwdata.nbr_proc = 0;
	g_cwdata.first_proc = NULL;
}

t_int32			cw_exit(t_int32 ecode, t_int32 usage, t_int8 *msg)
{
	if (g_cwdata.first_champ)
		del_champs();
	if (g_cwdata.first_proc)
		del_procs();
	if (g_cwdata.memory)
		free(g_cwdata.memory);
	if (g_cwdata.colors)
		free(g_cwdata.colors);
	ft_bzero(&g_cwdata, sizeof(t_cw_data));
	if (msg)
		ft_printf("\033[31m%s\033[00m\n", msg);
	if (usage)
		ft_printf("USAGE : > ./corewar [[-v level_verbose] "
			"[-dump nbr_cycles]] [[-n number] champion1.cor]\n");
	exit(ecode);
}
