/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dico.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 18:10:03 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 18:10:09 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DICO_H
# define FT_DICO_H

# include "libft.h"

typedef unsigned char	t_uchar;
typedef unsigned long	t_ulong;
typedef int				t_comp(const void *a, const void *b, size_t n);
typedef void			*t_copy(void *dst, const void *src, size_t n);
typedef void			t_del(void *content, size_t content_size);
typedef size_t			t_hash(const void *content, size_t content_size, \
									int is_char);

typedef struct			s_entry
{
	void				*key;
	void				*value;
	size_t				id;
	struct s_entry		*next;
}						t_entry;

typedef struct			s_dico
{
	size_t				size;
	t_entry				**map;
	size_t				limit;
	t_hash				*hashing;
	t_comp				*key_cmp;
	t_copy				*key_cpy;
	t_del				*key_del;
	size_t				key_size;
	t_comp				*value_cmp;
	t_copy				*value_cpy;
	t_del				*value_del;
	size_t				value_size;
	int					is_char;
}						t_dico;

t_dico					*dic_alloc(size_t nb_entries);
void					dic_set(t_dico *dico, void *key, void *value);
void					*dic_get(t_dico *dico, void *key);
void					dic_del(t_dico **dico);

# define DICO_MIN_SIZE 241
# define DICO_FACTOR 2
# define DICO_RESIZE_LIMIT 0.75

#endif
