/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:04:24 by scoron            #+#    #+#             */
/*   Updated: 2020/05/03 19:20:33 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	if (s1 == 0 || s2 == 0)
		return (0);
	if (!(res = (char *)malloc((ft_strlen(s1) +
						ft_strlen(s2) + 1) * sizeof(char))))
		return (0);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	j = -1;
	while (s2[++j])
		res[i + j] = s2[j];
	res[i + j] = 0;
	return (res);
}

char		*ft_strnjoin(int nb_str, ...)
{
	va_list	va;
	int		i;
	char	*temp;
	char	*res;

	va_start(va, nb_str);
	i = 0;
	temp = ft_strnew(0);
	while (++i <= nb_str)
	{
		res = ft_strjoin(temp, va_arg(va, char *));
		free(temp);
		temp = res;
	}
	va_end(va);
	return (res);
}
