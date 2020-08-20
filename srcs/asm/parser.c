/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:09:55 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:09:57 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void				verify_filename(t_int8 *name)
{
	size_t		len;
	size_t		ext_len;

	ext_len = ft_strlen(EXT_ASM);
	g_err.file = name;
	len = ft_strlen(name);
	if (len < ext_len + 1 || ft_strcmp(EXT_ASM, name + len - ext_len))
		err_exit(E_INPUT, "Invalid file name.");
}

void					parse(t_int8 *name)
{
	t_header	header;

	verify_filename(name);
	if ((g_err.fd = open(name, O_RDONLY)) == -1)
		err_exit(E_OPEN, name);
	ft_bzero(&header, sizeof(t_header));
	process_header(&header);
	init_dico();
	process_command();
	dic_del(&g_dico_labels);
	if (close(g_err.fd) == -1)
		err_exit(E_CLOSE, name);
	asm_write(name, &header);
}
