/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:09:31 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:09:33 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void			encode_arg_type(t_arg_type *type)
{
	t_uint8		encoding;

	encoding = 0;
	if (type[0] & ~T_LAB)
		encoding |= (((type[0] & ~T_LAB) >> 1) + 1) << 6;
	if (type[1] & ~T_LAB)
		encoding |= (((type[1] & ~T_LAB) >> 1) + 1) << 4;
	if (type[2] & ~T_LAB)
		encoding |= (((type[2] & ~T_LAB) >> 1) + 1) << 2;
	if (type[3] & ~T_LAB)
		encoding |= ((type[3] & ~T_LAB) >> 1) + 1;
	ar_append(g_result, (void *)(unsigned long)encoding, 1);
}

static t_bool		append_empty_args(t_command_output *output)
{
	t_uint8		i;
	t_uint8		length;

	i = 0;
	while (i < MAX_ARGS_NUMBER && (length = *(output->arg_sizeof + i)))
	{
		while (length--)
			ar_append(g_result, (void *)0, 1);
		i++;
	}
	return (!((*output->arg_type & T_LAB)
	|| (*(output->arg_type + 1) & T_LAB)
	|| (*(output->arg_type + 2) & T_LAB)
	|| (*(output->arg_type + 3) & T_LAB)));
}

static void			encode_addr(t_int8 *arg, t_uint8 *encoding,
		t_uint8 size, t_command_output *output)
{
	void		*label;
	t_uint32	addr;
	t_uint8		i;

	if (*arg == DIRECT_CHAR)
		arg++;
	if (*arg == LABEL_CHAR)
	{
		if (!(label = dic_get(g_dico_labels, arg + 1)))
			err_exit(E_INPUT, "Label not found in argument");
		addr = (t_uint32)label - output->loc - 1;
	}
	else
	{
		addr = (*arg == '-' ? ft_atoi_er(arg) :
				atoi_cor(arg, output->op->op_code));
		if (ft_no_numb(arg))
			err_exit(E_INPUT, "No value for address.");
	}
	encoding += size - 1;
	i = 0;
	while (i < size)
		*encoding-- = *((t_uint8 *)&addr + i++);
}

static void			encode_arg(t_command_input *input,
		t_command_output *output, t_uint8 *encoding)
{
	t_uint8		i;
	t_uint8		length;

	i = 0;
	while (i < MAX_ARGS_NUMBER && (length = *(output->arg_sizeof + i)))
	{
		if (length == sizeof(t_uint8))
		{
			*encoding = (t_uint8)ft_atoi_er(*(input->av + i) + 1);
			if (ft_no_numb(*(input->av + i) + 1))
				err_exit(E_INPUT, "No value for argument.");
			encoding++;
		}
		else
		{
			encode_addr(*(input->av + i),
					encoding, length, output);
			encoding += length;
		}
		i++;
	}
}

void				encode(t_command_input *input,
		t_command_output *output)
{
	size_t				post_empty_args;

	ar_append(g_result, (void *)(t_ulong)output->op->op_code, 1);
	if (output->op->carry)
		encode_arg_type(output->arg_type);
	post_empty_args = g_result->size;
	if (!append_empty_args(output))
		process_command();
	encode_arg(input, output, (t_uint8 *)g_result->data + post_empty_args);
}
