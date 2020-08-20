/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpacaud <tpacaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 15:08:41 by tpacaud           #+#    #+#             */
/*   Updated: 2020/06/23 14:18:22 by tpacaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**From hex of t_uint8 * to int
*/

void		hex_to_i(t_uint8 *content, t_uint32 size,
							t_uint32 is_ind)
{
	t_uint32 i;
	t_uint32 print;

	i = 0;
	print = ((is_ind && content[0] & 0x8) ? 0xFFFF : 0);
	while (i < size)
	{
		print = (print << 8);
		print |= content[i];
		i++;
	}
	ft_printf("%i", (t_int32)print);
}

/*
**Get and print param
*/

t_uint32	get_param(t_uint8 *str, t_uint32 mask,
							t_uint32 bitshift, t_uint32 pos)
{
	t_uint32 length;
	t_uint32 indirect;

	ft_printf("%c", get_arg_type_disasm((mask & str[1]) >> bitshift));
	indirect = (get_arg_type_disasm((mask & str[1]) >> bitshift) == 1) ? 1 : 0;
	if (((mask & str[1]) >> bitshift) == 0x2 ||
			((mask & str[1]) >> bitshift) == 0x3)
	{
		length = ((((mask & str[1]) >> bitshift) == 0x2) ?
			4 / (g_op_tab[(t_int32)str[0] - 1].dir_size + 1) : 2);
		hex_to_i(&str[pos], length, 0);
		ft_printf("%c", SEPARATOR_CHAR);
		return (length);
	}
	else
	{
		hex_to_i(&str[pos], (mask & str[1]) >> bitshift, indirect);
		ft_printf("%c", SEPARATOR_CHAR);
		return ((mask & str[1]) >> bitshift);
	}
}

/*
**Parsing and print each operation and get his params
*/

t_uint32	parse_disasm(t_uint8 *str)
{
	t_uint32 ret;

	if ((ret = 1) && str[0] > 0 && str[0] <= MAX_OP)
	{
		ft_printf("%s\t", g_op_tab[(t_int32)str[0] - 1].name);
		if (g_op_tab[(t_int32)(str[0] - 1)].params > 1 && ret++)
		{
			ret += get_param(str, 0xC0, 6, ret);
			ret += get_param(str, 0x30, 4, ret);
			if (g_op_tab[(t_int32)(str[0] - 1)].params > 2)
				ret += get_param(str, 0xC, 2, ret);
		}
		else if (g_op_tab[(t_int32)(str[0] - 1)].params == 1)
		{
			ft_printf("%c",
				get_arg_type_disasm(g_op_tab[(t_int32)str[0] - 1].type[0]));
			hex_to_i(&str[1], (4 / (g_op_tab[(t_int32)
			str[0] - 1].dir_size + 1)), ((str[0] == 9) ? 1 : 0));
			ret += (4 / (g_op_tab[(t_int32)str[0] - 1].dir_size + 1));
		}
		ft_printf("\n");
	}
	else
		ft_printf("OP_code inconnu\n");
	return (ret);
}

/*
**Main disassembling
*/

t_uint32	disasm(t_champ *champs)
{
	t_uint32 i;

	while (champs)
	{
		i = 0;
		ft_printf("\n\n----\n\n");
		ft_printf(".name \"%s\"\n", champs->name);
		ft_printf(".comment \"%s\"\n\n", champs->comment);
		while (i < champs->exec_size)
		{
			i += parse_disasm(&champs->exec[i]);
		}
		champs = champs->next;
	}
	return (0);
}
