/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:09:49 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:09:51 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_arg_type	parse_type(t_int8 *cmd)
{
	t_arg_type	type;
	t_int32		i;

	type = T_IND;
	if (*cmd == 'r')
	{
		if (ft_no_numb(++cmd))
			err_exit(E_INPUT, "No value for register");
		i = ft_atoi_err(cmd, 0);
		if (i < 1 || i > REG_NUMBER)
			err_exit(E_WARNING,
					COL_BYELLOW"REG_NUMBER value is out of bound." COL_RESET);
		type = T_REG;
	}
	else if (*cmd == DIRECT_CHAR && ++cmd)
		type = T_DIR;
	if (*cmd == LABEL_CHAR && type != T_REG)
		return (T_LAB | type);
	if (*cmd == '-' && ft_isdigit(*(cmd + 1)))
		cmd++;
	while (*cmd)
		if (!ft_isdigit(*cmd++))
			err_exit(E_INPUT, "Arg seems not to be a number.");
	return (type);
}

static t_uint8		parse_length(t_arg_type type, t_int32 size)
{
	if (type & T_REG)
		return (sizeof(t_uint8));
	else if (type & T_IND)
		return (sizeof(t_uint16));
	else if (type & T_DIR)
		return (size ? sizeof(t_uint16) : sizeof(t_uint32));
	return (0);
}

void				parse_args(t_command_input *input, \
							t_command_output *output)
{
	t_int32	i;

	if ((t_uint8)input->ac != output->op->params)
		err_exit(E_INPUT, "Invalid number of arguments for this op.");
	if (!input->ac)
		return ;
	i = 0;
	while (i < input->ac)
	{
		*(output->arg_type + i) = parse_type(*(input->av + i));
		*(output->arg_sizeof + i) = \
			parse_length(*(output->arg_type + i), \
							output->op->dir_size);
		if ((!(*(output->op->type + i)
		& *(output->arg_type + i) & ~T_LAB)))
			err_exit(E_INPUT, "Invalid arg type for this op.");
		i++;
	}
}
