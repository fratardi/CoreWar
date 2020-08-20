/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:09:58 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:10:00 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_cmd_part		read_label(t_int8 *label, size_t length, \
								t_command_input *command)
{
	char	*reader;

	reader = label;
	while ((size_t)(reader - label) < length)
		if (!ft_strchr(LABEL_CHARS, *reader++))
			err_exit(E_INPUT, "Invalid character in label.");
	if (length > LABEL_MAX_LEN)
		err_exit(E_INPUT, "Label seems too long");
	ft_memcpy(&command->label, label, length);
	*(command->label + length) = 0;
	return (C_LABEL);
}

static t_cmd_part		read_op(t_int8 *op, size_t length,
						t_command_input *command)
{
	if (length > OPCODE_MAX_LEN)
		err_exit(E_INPUT, "Op seems too long");
	ft_memcpy(&command->op, op, length);
	*(command->op + length) = 0;
	return (C_OP);
}

static t_cmd_part		read_arg(t_int8 *arg, size_t length, \
								t_command_input *command)
{
	char	*reader;
	char	*start;

	if (command->ac || !(reader = arg))
		return (C_ARG);
	while (!eol(*reader) && command->ac < MAX_ARGS_NUMBER)
	{
		reader = go_next_word(reader);
		start = reader;
		while (!eol(*reader) && *reader != SEPARATOR_CHAR)
			reader++;
		while (reader != start && (ft_isspace(*reader)
		|| *reader == SEPARATOR_CHAR || eol(*reader)))
			reader--;
		length = verify_length((size_t)(reader - start) + 1, command);
		ft_memcpy(command->av + command->ac, start, length);
		*(*(command->av + command->ac) + length) = 0;
		command->ac++;
		while (!eol(*reader) && *reader != SEPARATOR_CHAR)
			reader++;
		if (*reader == SEPARATOR_CHAR && !eol(*(reader + 1)))
			reader++;
	}
	return (C_ARG);
}

static t_cmd_part		read_command(t_int8 *line, \
									t_cmd_part part, t_command_input *command)
{
	char		*word;

	line = go_next_word(line);
	if (eol(*line))
		return (part);
	word = line;
	line = pass_word(line, part);
	if (*word == '.' && part == C_START)
		err_exit(E_INPUT, "Could not find .CMD");
	if (*(line - 1) == LABEL_CHAR)
	{
		if (part & C_OP || part & C_LABEL)
			err_exit(E_INPUT,
			"Label or op has already been found. (Or illegal '%' character)");
		part |= read_label(word, (size_t)(line - word - 1), command);
	}
	else if (!(part & C_OP))
		part |= read_op(word, (size_t)(line - word), command);
	else
		part |= read_arg(word, (size_t)(line - word), command);
	return (read_command(line, part, command));
}

void					process_command(void)
{
	t_int32			check;
	t_cmd_part		cmd_part;
	t_command_input	command;

	ft_bzero(&command, sizeof(t_command_input));
	ft_memdel((void **)&(g_err.li));
	if (!(check = get_next_line(g_err.fd, &(g_err.li))))
		return ;
	else if (check == -1)
		err_exit(E_READ, NULL);
	g_err.li_pos += 1;
	cmd_part = read_command(g_err.li, C_START, &command);
	if (!(!cmd_part || (cmd_part & C_LABEL && !(cmd_part & C_OP))
	|| (cmd_part & C_OP && cmd_part & C_ARG)))
		err_exit(E_INPUT, "Instruction invalid (format or other)");
	if (cmd_part)
		parse_command(&command);
	process_command();
}
