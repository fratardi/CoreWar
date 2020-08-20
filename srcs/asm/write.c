/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:10:07 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:10:09 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

uint32_t		convert_uint32(uint32_t d)
{
	return ((d & 0x000000ff) << 24
			| (d & 0x0000ff00) << 8
			| (d & 0x00ff0000) >> 8
			| (d & 0xff000000) >> 24);
}

static char		*get_cor_name(t_int8 *asm_name)
{
	char	*cor_name;
	size_t	length;
	size_t	len_ext;

	len_ext = ft_strlen(EXT_COR);
	length = ft_strlen(asm_name) + len_ext;
	cor_name = malloc(length);
	if (!cor_name)
		return (NULL);
	ft_memcpy(cor_name, asm_name, length - (len_ext + 1));
	ft_memcpy(cor_name + length - (len_ext + 1), EXT_COR, len_ext + 1);
	return (cor_name);
}

static void		add_header(t_header *header)
{
	t_uint8	*p;
	size_t	size;

	header->magic = convert_uint32(COREWAR_EXEC_MAGIC);
	header->prog_size = convert_uint32(g_result->size);
	size = (size_t)sizeof(t_header);
	p = (t_uint8 *)header + size - 1;
	while (size--)
		ar_insert(g_result, (void *)(t_ulong) * p--, 1, 0);
}

void			asm_write(t_int8 *asm_name, t_header *header)
{
	char	*cor_name;

	if (!g_result->size)
		err_exit(E_INPUT, "Content should be minimum one byte");
	cor_name = get_cor_name(asm_name);
	if (!cor_name || (g_err.fd = open(cor_name,
			O_CREAT | O_WRONLY, 0644)) == -1)
		err_exit(E_OPEN, cor_name);
	add_header(header);
	write(1, "Compiling program to ", 21);
	write(1, cor_name, ft_strlen(cor_name));
	write(1, "\n", 1);
	if ((size_t)write(g_err.fd, g_result->data,
			g_result->size) != g_result->size)
		err_exit(E_WRITE, cor_name);
	if (close(g_err.fd) == -1)
		err_exit(E_CLOSE, cor_name);
	ft_memdel((void *)&cor_name);
	ar_del(&g_result);
	ft_strlst_free(g_err.warnings);
}
