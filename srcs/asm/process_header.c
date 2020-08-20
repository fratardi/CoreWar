/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:10:04 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:10:06 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void				parse_header(t_int8 *line, \
									t_cmd_part current, t_header *header)
{
	size_t		len;

	if (current & C_NAME)
	{
		if ((len = ft_strlen(line)) > PROG_NAME_LENGTH)
			err_exit(E_INPUT, "Header not valid (name too long).");
		ft_memcpy(&header->prog_name, line, len);
	}
	else if (current & C_COMMENT && !(current & C_MULTILINE_COMMENT))
	{
		if ((len = ft_strlen(line)) > COMMENT_LENGTH)
			err_exit(E_INPUT, "Header not valid (comment too long).");
		ft_memcpy(&header->comment, line, len);
	}
}

static t_cmd_part		process_id(t_int8 *line)
{
	if (!ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		return (C_NAME);
	if (!ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		return (C_COMMENT);
	err_exit(E_INPUT, "Header not valid (id not recognized).");
	return (C_START);
}

static t_cmd_part		verify_header(t_int8 *line, t_header *header)
{
	t_cmd_part	current;

	while (!eol(*line) && ft_isspace(*line))
		line++;
	if (eol(*line))
		return (C_START);
	current = process_id(line);
	while (!eol(*line) && !ft_isspace(*line) && *line != '"')
		line++;
	while (!eol(*line) && ft_isspace(*line) && *line != '"')
		line++;
	process_quotes(line, &current);
	if (current & C_MULTILINE_COMMENT)
		process_multiline_comment(line + 1, header);
	parse_header(line + 1, current, header);
	return (current);
}

void					process_header(t_header *header)
{
	t_cmd_part	current;
	t_cmd_part	tmp;

	g_err.li = NULL;
	current = C_START;
	while (!(current & C_NAME && current & C_COMMENT))
	{
		tmp = C_START;
		if (get_next_line(g_err.fd, &(g_err.li)) <= 0)
			err_exit(E_READ, NULL);
		g_err.li_pos += 1;
		if (current & (tmp = verify_header(g_err.li, header)))
			err_exit(E_INPUT, "Header not valid (double name or comment).");
		current |= tmp;
		ft_memdel((void **)&(g_err.li));
	}
}
