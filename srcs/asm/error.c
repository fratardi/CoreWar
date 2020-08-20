/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 11:02:38 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 11:02:40 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>
#include <unistd.h>

static t_int32	get_index(t_uint8 err_type)
{
	t_int32	index;

	index = 0;
	while (err_type && (err_type != 0x1))
	{
		err_type = err_type >> 1;
		index++;
	}
	return (index);
}

static t_int32	clean(void)
{
	if (g_result)
		ar_del(&g_result);
	if (g_dico_labels)
		dic_del(&g_dico_labels);
	if (g_err.li)
		ft_memdel((void **)&g_err.li);
	if (g_err.fd != -1)
		close(g_err.fd);
	ft_strlst_free(g_err.warnings);
	return (0);
}

static void		print_color(t_int8 *error_type)
{
	ft_dprintf(2, COL_CYAN "%s", g_err.file);
	if (g_err.li_pos)
		ft_dprintf(2, ":%d", g_err.li_pos);
	ft_dprintf(2, ": " COL_RED "%s" COL_RESET "\n", error_type);
	if (g_err.li)
	{
		ft_dprintf(2, "%s\n", g_err.li);
		ft_dprintf(2, "\t" COL_GREEN "^" COL_RESET "\n");
	}
}

static t_int32	check_warning(t_uint8 err_type, t_int8 *msg)
{
	t_int32	i;

	if (!(err_type & E_WARNING))
		return (1);
	i = 0;
	while (i < MAX_WARNINGS && g_err.warnings[i])
	{
		if (!(ft_strcmp(msg, g_err.warnings[i])))
			return (0);
		i++;
	}
	if (i < MAX_WARNINGS && g_err.warnings[i] == NULL)
	{
		g_err.warnings[i] = ft_strdup(msg);
		g_err.warnings[i + 1] = NULL;
	}
	return (1);
}

t_bool			err_exit(t_uint8 err_type, t_int8 *msg)
{
	const char	*error[] = {
		COL_BYELLOW "WARNING !\n" COL_RESET,
		"Right usage: .\\asm [NAME].s",
		": Couldn't read file",
		": Couldn't open file: ",
		": Couldn't close file: ",
		": Couldn't write to file: ",
		COL_BRED "Unknown param error" COL_RESET,
	};

	if (check_warning(err_type, msg) == 0)
		return (FALSE);
	if (!(err_type & (E_INPUT | E_USAGE | E_WARNING)))
		ft_dprintf(2, g_err.champ);
	if (msg)
		err_type & E_INPUT ? print_color(msg) :
		ft_dprintf(2, "%s%s\n", error[get_index(err_type)], msg);
	else
		ft_dprintf(2, "%s\n", error[get_index(err_type)]);
	if (!(err_type & E_WARNING))
		exit(clean() || EXIT_FAILURE);
	return (FALSE);
}
