/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rank.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:02:14 by scoron            #+#    #+#             */
/*   Updated: 2020/07/02 16:19:34 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			rank_shift(t_champ *current)
{
	t_champ *tmp;

	while (current)
	{
		if (current->next && current->next->next
			&& current->next->next->nb - 1 == -current->next->nb)
		{
			tmp = current->next->next;
			current->next->next = tmp->next;
			tmp->next = current->next;
			current->next = tmp;
		}
		current = current->next;
		if (current && current->nb < 0)
			current->nb--;
	}
}

void			rank_index(void)
{
	t_champ *current;
	t_int32	nb;

	current = g_cwdata.first_champ;
	nb = 0;
	while (current)
	{
		nb -= 1;
		current->nb = nb;
		current = current->next;
	}
}

void			rank_reverse(void)
{
	t_champ *current;
	t_champ *last;

	current = g_cwdata.first_champ;
	if (!current->next)
		return ;
	while (current->next->next)
		current = current->next;
	last = current->next;
	current->next->next = current;
	while (g_cwdata.first_champ != g_cwdata.first_champ->next->next)
	{
		current = g_cwdata.first_champ;
		while (current->next->next->next != current->next)
			current = current->next;
		current->next->next = current;
	}
	g_cwdata.first_champ->next = NULL;
	g_cwdata.first_champ = last;
}

void			clean_rank(void)
{
	t_champ *current;

	current = g_cwdata.first_champ;
	while (current)
	{
		if (current->nb > 0)
		{
			current->nb *= -1;
			if (current->next && current->next->nb == current->nb)
				rank_shift(current);
		}
		current = current->next;
	}
	rank_index();
	rank_reverse();
}
