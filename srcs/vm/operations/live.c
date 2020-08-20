/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:17:03 by scoron            #+#    #+#             */
/*   Updated: 2020/06/23 14:04:52 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_int32		cw_live(t_cw_proc *current, t_uint8 *pos)
{
	t_int32		nb_chmp;
	t_champ		*champ;
	t_uint8		*cursor;

	cursor = cw_jump(pos, 1, 0);
	nb_chmp = cw_read(cursor, sizeof(nb_chmp));
	current->last_live = g_cwdata.nbr_cycle;
	if ((champ = find_champ(nb_chmp)))
	{
		if (g_cwdata.verbose == 1)
			ft_printf("live : Champion %d (%s) is said to be alive\n",
					-champ->nb, champ->name);
		++champ->lives_count;
		champ->last_live = g_cwdata.nbr_cycle;
	}
	++g_cwdata.lives_count;
	current->pos = cw_jump(pos, 5, 42);
	return (SUCCESS);
}
