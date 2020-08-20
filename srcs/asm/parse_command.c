/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:09:52 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:09:55 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		parse_label(t_int8 *label, t_uint32 loc)
{
	if (!*label)
		return ;
	if (dic_get(g_dico_labels, label))
		err_exit(E_WARNING, COL_BYELLOW "Duplicated label." COL_RESET);
	dic_set(g_dico_labels, ft_strdup(label), (void *)(t_ulong)loc + 1);
}

static t_op		*parse_op(t_int8 *op, t_command_output *command)
{
	t_op	*op_pts;

	op_pts = g_op_tab;
	while ((size_t)(op_pts - g_op_tab) < MAX_OP \
			&& ft_strcmp(op_pts->name, op))
		op_pts++;
	if ((size_t)(op_pts - g_op_tab) == MAX_OP)
		err_exit(E_INPUT, "Op not found.");
	command->op = op_pts;
	return (op_pts);
}

void			parse_command(t_command_input *input)
{
	t_command_output	output;

	if (g_result->size > CHAMP_MAX_SIZE)
		err_exit(E_WARNING, COL_BYELLOW "File too long." COL_RESET);
	ft_bzero(&output, sizeof(t_command_output));
	output.loc = g_result->size;
	parse_label(input->label, g_result->size);
	if (*input->op)
	{
		parse_op(input->op, &output);
		parse_args(input, &output);
		encode(input, &output);
	}
}
