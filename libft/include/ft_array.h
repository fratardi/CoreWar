/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 18:12:24 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 18:12:25 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ARRAY_H
# define FT_ARRAY_H

# include <stddef.h>

typedef struct	s_array
{
	void		*data;
	size_t		size;
	size_t		limit;
	size_t		type_size;
}				t_array;

t_array			ar_new(size_t type_size);
t_array			*ar_alloc(size_t type_size);
int				ar_reserve(t_array *arr, size_t reserve_sup);
int				ar_resize(t_array *arr, size_t new_size);
void			ar_clear(t_array *arr);
void			ar_del(t_array **arr);
int				ar_append(t_array *self, void const *data, size_t datalen);
int				ar_append_free(t_array *arr, void *data, size_t datalen);
int				ar_append_char(t_array *arr, char data);
int				ar_insert(t_array *self, void const *data,
							size_t datalen, size_t index);
int				ar_popindex(t_array *arr, size_t index, size_t len);
void			*ar_get(t_array *a, size_t i);
void			*ar_end(t_array *a);
size_t			ar_offset(t_array *a, size_t i);

# define ARR_MIN_SIZE 16
# define ARR_FACTOR 2

#endif
