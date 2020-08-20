/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpacaud <tpacaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 13:24:43 by tpacaud           #+#    #+#             */
/*   Updated: 2020/06/19 15:51:48 by tpacaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_uint32		check_param(t_int8 *str, t_int8 *next)
{
	if (!(ft_strcmp(str, "-n")) || !(ft_strcmp(str, "-dump")))
		return (check_option_next(str, next));
	else if (!(ft_strcmp(str, "-v")) && next)
		return (0xFB);
	else if (ft_strchr(str, '.'))
	{
		while (*str && (ft_strcmp(str, ".cor") || ft_strlen(str) != 4))
			str++;
		if (!(ft_strcmp(str, ".cor")))
			return (0xFA);
	}
	return (0);
}

t_int32			cw_parse_options(t_int32 ac, t_int8 **av)
{
	t_int32		i;
	t_uint32	param;
	char		*next;

	i = 0;
	while (++i < ac)
	{
		next = i + 1 >= ac ? NULL : av[i + 1];
		if (!(param = check_param(av[i], next)))
			return (-1);
		else if (i + 1 < ac && param == 0xFD)
			g_cwdata.dump = ft_atoi_err(av[++i], -1);
		else if (param == 0xFB)
			i += check_optional_next(param, next);
		else
			return (i - 1);
	}
	return (i - 1);
}

void			cw_parsing_loop(t_int32 ac, t_int8 **av, t_int32 i)
{
	t_uint32	param;
	char		*next;
	t_int32		rank;

	while (++i < ac)
	{
		rank = 0;
		if (g_cwdata.nbr_champ >= MAX_PLAYERS)
			cw_exit(FAILED, 0, "ERROR : too many champions");
		next = i + 1 >= ac ? NULL : av[i + 1];
		if ((param = check_param(av[i], next)) > 0 && param <= MAX_PLAYERS)
		{
			rank = param;
			i += 2;
			next = i + 1 >= ac ? NULL : av[i + 1];
			if (i >= ac || check_param(av[i], next) != 0xFA)
				cw_exit(FAILED, 1, "ERROR: missing file after option -n");
		}
		else if (param != 0xFA)
			cw_exit(FAILED, 1, "ERROR : wrong param");
		read_champ(av[i], rank);
	}
}

t_uint32		cw_parsing(t_int32 ac, t_int8 **av)
{
	t_int32		i;

	if ((i = cw_parse_options(ac, av)) == -1)
		cw_exit(FAILED, 1, "ERROR : failure during option parsing");
	cw_parsing_loop(ac, av, i);
	if (g_cwdata.nbr_champ == 0)
		cw_exit(FAILED, 1, "ERROR: no champions");
	clean_rank();
	return (SUCCESS);
}
