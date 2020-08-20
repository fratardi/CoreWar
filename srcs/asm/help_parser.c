/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:09:38 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:09:40 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			*go_next_word(t_int8 *str)
{
	while (!eol(*str) && ft_isspace(*str))
		str++;
	return (str);
}

char			*pass_word(t_int8 *str, t_cmd_part part)
{
	while (!eol(*str) && !(ft_isspace(*str))
		&& (part & C_OP || *str != DIRECT_CHAR))
		str++;
	return (str);
}

size_t			verify_length(size_t length, t_command_input *command)
{
	if (command->ac + 1 > MAX_ARGS_NUMBER)
		err_exit(E_INPUT, "Too many args.");
	if (length > ARG_MAX_LEN)
		err_exit(E_INPUT, "An arg is too long.");
	return (length);
}

t_int32			eol(t_int8 c)
{
	if (c == '\0' || c == COMMENT_CHAR || c == COMMENT_CHAR_2)
		return (TRUE);
	return (FALSE);
}

t_uint32		atoi_cor(const t_int8 *str, t_int32 opcode)
{
	t_int32				i;
	unsigned long long	result;
	unsigned long long	limit;
	char				c_limit;

	i = 0;
	result = 0;
	limit = opcode == 1 ? 922337203685477580 : 429496729;
	c_limit = opcode == 1 ? '7' : '5';
	while (str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > limit)
			return (0xffffffff);
		if (result == limit && str[i] > c_limit)
			return (0xffffffff);
		result = 10 * result + str[i++] - '0';
	}
	return ((t_uint32)result);
}
