/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpacaud <tpacaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 11:41:51 by tpacaud           #+#    #+#             */
/*   Updated: 2020/06/23 14:20:50 by tpacaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <unistd.h>

void		get_hex(t_uint8 *buf, t_uint8 to_convert)
{
	static char	tab[17] = "0123456789ABCDEF";
	t_uint32	i;
	t_int32		size;

	i = 0;
	buf[0] = '0';
	buf[1] = '0';
	if (to_convert == 0)
		return ;
	size = ft_size_hexa((t_uint64)to_convert);
	if (size > 1)
		size = 1;
	while (size >= 0)
	{
		buf[size] = (tab[to_convert % 16]);
		to_convert = to_convert / 16;
		size--;
	}
	return ;
}

/*
**Is a carriage at this position ?
*/

t_int32		carriage_here(t_uint32 curr_pos)
{
	t_cw_proc *proc;

	proc = g_cwdata.first_proc;
	while (proc)
	{
		if (proc->pos == g_cwdata.memory + curr_pos)
			return (proc->nb);
		proc = proc->next;
	}
	return (-1);
}

/*
**Buffer initialisation before print
*/

t_uint32	init_buffer(t_uint32 i,
							t_uint32 buf_pos, t_uint8 *buf)
{
	if (carriage_here(i) >= 0)
	{
		join_buf(&buf[buf_pos], "\033[7;48;3", 9);
		buf_pos += 8;
		join_color_code(&buf[buf_pos], carriage_here(i));
		join_buf(&buf[buf_pos + 1], "m", 1);
		buf_pos += 2;
	}
	else if (g_cwdata.colors[i] > 0)
	{
		join_buf(&buf[buf_pos], "\033[3", 4);
		buf_pos += 3;
		join_color_code(&buf[buf_pos], g_cwdata.colors[i]);
		join_buf(&buf[buf_pos + 1], "m", 1);
		buf_pos += 2;
	}
	get_hex(&buf[buf_pos], g_cwdata.memory[i]);
	buf_pos += 2;
	join_buf(&buf[buf_pos], "\033[0;00;00m ", 12);
	buf_pos += 11;
	return (buf_pos);
}

/*
**Print buffer and clear it
*/

void		print_buffer(t_uint8 *buf, t_uint32 *buf_pos, t_uint32 line)
{
	ft_printf("0x%.4x : ", line);
	write(1, &buf[0], *buf_pos);
	write(1, "\n", 1);
	*buf_pos = 0;
	ft_bzero(&buf[0], MEM_SIZE);
}

/*
**Print the arena with a refresh rate
*/

void		print_refresh_area(t_int32 init)
{
	t_uint32	i;
	t_uint32	y;
	t_uint8		buf[MEM_SIZE + 1];
	t_uint32	buf_pos;

	i = MEM_SIZE / 64 + g_cwdata.nbr_proc;
	y = 1;
	ft_bzero(&buf[0], MEM_SIZE);
	buf_pos = 0;
	while (init == 0 && i--)
		write(1, "\033[F\033[J", 6);
	print_head();
	i = 0;
	while (i < MEM_SIZE)
	{
		buf_pos = init_buffer(i, buf_pos, &buf[0]);
		if (!(y % 64))
			print_buffer(&buf[0], &buf_pos, y);
		i++;
		y++;
	}
	read(1, buf, 1);
}
