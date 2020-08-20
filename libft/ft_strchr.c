/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 11:46:42 by scoron            #+#    #+#             */
/*   Updated: 2020/05/03 07:27:22 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strchr(const char *s, int c)
{
	int			i;

	i = -1;
	while (*(s + ++i))
		if (*(s + i) == (unsigned char)c)
			return ((char *)s + i);
	return (*((char *)s + i) == (unsigned char)c ? (char *)s + i : 0);
}

int				ft_strchri(const char *s, int c)
{
	int			i;

	i = -1;
	while (*(s + ++i))
		if (*(s + i) == (unsigned char)c)
			return (i);
	return (*((char *)s + i) == (unsigned char)c ? i : -1);
}

int				exist_in(char i, char const *str)
{
	char const	*p = str;

	while (*p != '\0' && *p != i)
		p++;
	return (*p == '\0' ? -1 : (int)(p - str));
}
