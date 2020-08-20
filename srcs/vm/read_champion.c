/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpacaud <tpacaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 15:42:01 by tpacaud           #+#    #+#             */
/*   Updated: 2020/06/13 02:57:08 by tpacaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <unistd.h>
#include <fcntl.h>

t_int32		find_rank(t_int32 rank)
{
	t_champ	*current;

	current = g_cwdata.first_champ;
	if (rank == 0 && --rank)
		while (current)
		{
			if (current->nb == rank || current->nb == -1 * rank)
			{
				rank--;
				current = g_cwdata.first_champ;
			}
			else
				current = current->next;
		}
	else
		while (current)
		{
			if (current->nb == rank)
				cw_exit(FAILED, 1, "ERROR : Duplicate -n number");
			current = current->next;
		}
	return (rank);
}

/*
 ** Header size.
*/

t_uint32	get_size(void)
{
	t_uint32 size;

	size = sizeof(COREWAR_EXEC_MAGIC);
	size += PROG_NAME_LENGTH;
	size += 8;
	size += COMMENT_LENGTH;
	size += 4;
	return (size);
}

/*
 ** Inserting the champion in the linked list based on its nb.
*/

void		champ_push(t_champ *champ)
{
	t_champ *tmp;

	champ = ft_memcpy(ft_memalloc(sizeof(t_champ)), champ, sizeof(t_champ));
	if (!g_cwdata.first_champ
		|| abs(g_cwdata.first_champ->nb) >= abs(champ->nb))
	{
		champ->next = g_cwdata.first_champ;
		g_cwdata.first_champ = champ;
	}
	else
	{
		tmp = g_cwdata.first_champ;
		while (tmp->next && abs(tmp->next->nb) < abs(champ->nb))
			tmp = tmp->next;
		champ->next = tmp->next;
		tmp->next = champ;
	}
	++g_cwdata.nbr_champ;
}

void		read_champ(const t_int8 *cor, t_int32 rank)
{
	t_int32	fd;
	ssize_t	size;
	t_uint8	buf[MEM_SIZE];
	t_champ	champ;

	if ((fd = open(cor, O_RDONLY)) < 0)
		cw_exit(FAILED, 0, "ERROR: Could not open file");
	if (read(fd, &buf, get_size()) < get_size())
		cw_exit(FAILED, 0, "ERROR: Header is invalid");
	if (*(t_uint32 *)buf != convert_magic(COREWAR_EXEC_MAGIC))
		cw_exit(FAILED, 0, "ERROR: Invalid magic number");
	ft_bzero(&champ, sizeof(t_champ));
	ft_memcpy((void*)(champ.name), buf + sizeof(t_uint32), PROG_NAME_LENGTH);
	ft_memcpy((void*)(champ.comment), buf
		+ sizeof(t_uint32) + PROG_NAME_LENGTH + 8, COMMENT_LENGTH + 1);
	if ((size = read(fd, &buf, CHAMP_MAX_SIZE + 1)) <= 0)
		cw_exit(FAILED, 0, "ERROR: empty champion");
	if (size > CHAMP_MAX_SIZE)
		cw_exit(FAILED, 0, "ERROR: champion too large");
	if (close(fd) < 0)
		cw_exit(FAILED, 0, "ERROR: could not close file");
	champ.nb = find_rank(rank);
	champ.exec_size = (size_t)size;
	ft_memcpy(champ.exec, buf, champ.exec_size);
	champ_push(&champ);
}
