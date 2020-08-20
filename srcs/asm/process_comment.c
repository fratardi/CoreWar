/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_comment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:10:02 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:10:03 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_int32	verify_after_quotes(t_int8 *line)
{
	while (!eol(*line))
		if (!ft_isspace(*line++))
			err_exit(E_INPUT,
					"Header is not valid (look after quotes).");
	return (TRUE);
}

static size_t	cpy_part_comment(t_int8 *line,
		t_header *header, size_t comment_len)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	if (line_len + comment_len + 1 > COMMENT_LENGTH)
		err_exit(E_INPUT, "Header is not valid (look at comment).");
	ft_memcpy(header->comment + comment_len, line, line_len);
	*(header->comment + comment_len + line_len) = '\n';
	return (line_len + 1);
}

void			process_multiline_comment(t_int8 *line, t_header *header)
{
	size_t	comment_len;

	comment_len = cpy_part_comment(line, header, 0);
	while (TRUE)
	{
		ft_memdel((void **)&(g_err.li));
		if (get_next_line(g_err.fd, &(g_err.li)) <= 0)
			err_exit(E_INPUT, "Header is not valid (second quote).");
		g_err.li_pos += 1;
		if ((line = ft_strchr(g_err.li, '"')))
		{
			*line = '\0';
			verify_after_quotes(line + 1);
			comment_len += cpy_part_comment(g_err.li, header, comment_len);
			*(header->comment + comment_len - 1) = '\0';
			break ;
		}
		comment_len += cpy_part_comment(g_err.li, header, comment_len);
	}
	ft_memdel((void **)&(g_err.li));
}

void			process_quotes(t_int8 *line, t_cmd_part *current)
{
	if (*line != '"')
		err_exit(E_INPUT, "Header is not valid (first quote).");
	++line;
	while (*line && *line != '"')
		line++;
	if (*line != '"')
		*current |= C_MULTILINE_COMMENT;
	else
	{
		*line = '\0';
		verify_after_quotes(line + 1);
	}
}
