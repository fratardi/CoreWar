/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_champion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpacaud <tpacaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:39:44 by tpacaud           #+#    #+#             */
/*   Updated: 2020/06/19 02:00:50 by tpacaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_champion_exec(t_uint8 *str, t_uint32 size)
{
	t_uint32 i;

	i = 0;
	while (i < size)
	{
		ft_hexfloat(&str[i], 1);
		ft_printf(" ");
		i++;
	}
}

void	print_champions_list(t_champ *champs)
{
	ft_printf("Here come the champions...\n");
	while (champs)
	{
		ft_printf("Champion Name = \033[33m%s\033[00m\n", champs->name);
		ft_printf("Champion Comment = \033[33m%s\033[00m\n", champs->comment);
		ft_printf("Champion Exec code size = \033[33m%zu\033[00m\n",
				champs->exec_size);
		ft_printf("EXEC_CODE :\n\033[33m");
		print_champion_exec(champs->exec, champs->exec_size);
		ft_printf("\033[00m\n\n\n");
		champs = champs->next;
	}
}
