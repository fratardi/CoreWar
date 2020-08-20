/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 13:39:43 by scoron            #+#    #+#             */
/*   Updated: 2019/03/06 13:10:55 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*res;
	int		i;

	if (!(res = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1))))
		return (0);
	i = -1;
	while (src[++i])
		res[i] = src[i];
	res[i] = '\0';
	return (res);
}

char	**ft_strdup_p(char **src)
{
	char	**res;
	int		len;
	int		i;

	len = 0;
	while (src[len])
		len++;
	if (!(res = (char **)malloc(sizeof(char *) * len + 1)))
		return (0);
	i = -1;
	while (src[++i])
		res[i] = src[i];
	res[i] = NULL;
	return (res);
}
