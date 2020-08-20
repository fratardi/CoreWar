/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpacaud <tpacaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:02:14 by tpacaud           #+#    #+#             */
/*   Updated: 2020/06/19 15:37:18 by tpacaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <unistd.h>

t_cw_data		g_cwdata =
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};

void	cw_write_int(t_uint8 *pos, t_uint8 *src, t_int32 color)
{
	size_t		size;
	t_uint32	i;
	t_uint32	k;

	size = sizeof(t_int32);
	i = 0;
	while (i < size)
	{
		k = pos - g_cwdata.memory;
		g_cwdata.memory[k] = *src;
		g_cwdata.colors[k] = color;
		pos = cw_jump(pos, 1, 0);
		i++;
		src++;
	}
}

void	cw_init(t_int32 argc, t_int8 **argv)
{
	g_cwdata.cycles_to_die = CYCLE_TO_DIE;
	if (!(g_cwdata.memory = (t_uint8 *)malloc(sizeof(t_uint8)
			* (MEM_SIZE + 1)))
	|| !(g_cwdata.colors = (t_uint32 *)malloc(sizeof(t_uint32)
			* (MEM_SIZE + 1))))
		cw_exit(FAILED, 0, "ERROR : Could not malloc\n");
	ft_bzero(g_cwdata.memory, MEM_SIZE + 1);
	ft_bzero(g_cwdata.colors, MEM_SIZE + 1);
	cw_parsing(argc, argv);
	init_arena();
	if (g_cwdata.verbose == 3)
		disasm(g_cwdata.first_champ);
	if (g_cwdata.verbose > 3)
		print_refresh_area(1);
}

t_int32	main(t_int32 argc, t_int8 **argv)
{
	if (argc < 2)
		cw_exit(FAILED, 1, "ERROR : No champion");
	cw_init(argc, argv);
	cw_run();
	return (cw_exit(SUCCESS, 0, NULL));
}
