/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:09:18 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:09:30 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_error					g_err = {NULL, NULL, NULL, NULL, 0, 0};
t_array					*g_result = NULL;
t_dico					*g_dico_labels = NULL;

static t_int32		comp_str(const void *s1, const void *s2, size_t n)
{
	(void)n;
	return (ft_strcmp(*(t_int8 **)s1, *(t_int8 **)s2));
}

static void			free_str(void *str, size_t size)
{
	(void)size;
	free(str);
}

void				init_dico(void)
{
	g_result = ar_alloc(sizeof(t_uint8));
	g_dico_labels = dic_alloc(0);
	g_dico_labels->key_del = free_str;
	g_dico_labels->key_cmp = comp_str;
	g_dico_labels->value_size = sizeof(t_uint32);
	g_dico_labels->is_char = 1;
}

void				init_global_err(t_int8 *champ)
{
	ft_bzero(&g_err, sizeof(t_error));
	g_err.fd = -1;
	g_err.champ = champ;
	if (!(g_err.warnings = malloc(sizeof(t_int8 *) * MAX_WARNINGS)))
		exit(EXIT_FAILURE);
	ft_bzero(g_err.warnings, MAX_WARNINGS);
}

t_int32				main(t_int32 ac, t_int8 **av)
{
	init_global_err(*av++);
	if (ac != 2)
		err_exit(E_USAGE, NULL);
	else
		parse(*av);
	return (EXIT_SUCCESS);
}
