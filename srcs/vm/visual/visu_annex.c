/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_annex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpacaud <tpacaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:17:03 by tpacaud           #+#    #+#             */
/*   Updated: 2020/06/23 14:04:52 by tpacaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**Join color code to buffer
*/

void		join_color_code(t_uint8 *buf, t_uint32 color_code)
{
	if (color_code > 10)
		buf[0] = 0;
	buf[0] = color_code + 48;
}

/*
**Join something to buffer
*/

void		join_buf(t_uint8 *buf, t_int8 *to_join, t_uint32 size)
{
	t_uint32 i;

	i = 0;
	while (i < size)
	{
		buf[i] = (t_uint8)to_join[i];
		i++;
	}
}

/*
**Bzero color t_int32 tab
*/

void		clear_color(void)
{
	t_uint32 i;

	i = 0;
	while (i < MEM_SIZE)
	{
		g_cwdata.colors[i] = 0;
		i++;
	}
}

/*
**Print HEAD
*/

void		print_head(void)
{
	t_cw_proc	*proc;

	ft_printf("\033[F\033[33m*******************************");
	ft_printf("**********************************************");
	ft_printf("************** NBR_CYCLES %zu *", g_cwdata.nbr_cycle);
	ft_printf("***************************************************");
	ft_printf("******************************************\n\033[00m");
	proc = g_cwdata.first_proc;
	while (proc)
	{
		if (proc->cycles_left <= 1 && *proc->pos >= 0x1 && *proc->pos <= MAX_OP)
			ft_printf("\033[%dmProcess %d (%s) is about to execute %s\n\033[0m",
					proc->nb + 30, proc->nb, proc->champ->name,
					g_op_tab[*proc->pos - 1].name);
		else
			ft_printf("\033[%dmProcess %d (%s) is sleeping\n\033[0m",
					proc->nb + 30, proc->nb, proc->champ->name);
		proc = proc->next;
	}
}
