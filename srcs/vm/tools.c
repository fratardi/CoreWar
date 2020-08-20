/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpacaud <tpacaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:02:14 by tpacaud           #+#    #+#             */
/*   Updated: 2020/06/19 15:37:18 by tpacaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_uint32	check_optional_next(t_uint32 param, t_int8 *next)
{
	t_int32 i;

	if (param == 0xFB)
		g_cwdata.verbose = abs(ft_atoi_err(next, -1));
	i = ft_atoi_err(next, -1) < 0 ? 0 : 1;
	return (i);
}

t_uint32	check_option_next(t_int8 *str, t_int8 *next)
{
	t_int32		pos;

	if (next && (pos = ft_atoi_err(next, -1)) > -1)
	{
		if (pos > 0 && pos <= MAX_PLAYERS && !(ft_strcmp(str, "-n")))
			return (pos);
		else if (!(ft_strcmp(str, "-dump")))
			return (0xFD);
	}
	return (0);
}

t_champ		*find_champ(t_int32 nb)
{
	t_champ *champ;

	champ = g_cwdata.first_champ;
	while (champ)
	{
		if (champ->nb == nb)
			break ;
		champ = champ->next;
	}
	return (champ);
}

t_uint32	cw_size_param(t_uint8 param, t_uint8 dir_size)
{
	if (param == IND_CODE)
		return (2);
	else if (param == DIR_CODE)
		return (dir_size);
	else if (param == REG_CODE)
		return (1);
	return (0);
}

t_uint32	error_jump(t_uint8 *pos, t_uint8 opc)
{
	t_uint8 param_code;
	t_uint8 nb;
	t_uint8 dir_size;
	t_int32	res;

	res = 2;
	nb = g_op_tab[opc - 1].params;
	dir_size = g_op_tab[opc - 1].dir_size ? 2 : 4;
	param_code = *cw_jump(pos, 1, 0);
	res += cw_size_param((param_code & 0xc0) >> 6, dir_size);
	if (nb > 1)
		res += cw_size_param((param_code & 0x30) >> 4, dir_size);
	if (nb > 2)
		res += cw_size_param((param_code & 0x0c) >> 2, dir_size);
	return (res);
}
