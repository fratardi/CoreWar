/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 16:13:58 by jubeal            #+#    #+#             */
/*   Updated: 2019/03/05 08:11:52 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_copydup(char *dest, const char *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && str[i])
	{
		dest[i] = str[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char		*ft_strndup(const char *s, size_t n)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	str = ft_copydup(str, s, n);
	str[n] = '\0';
	return (str);
}

static char	**ft_copydup_p(char **dest, char **str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && str[i])
	{
		dest[i] = str[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = NULL;
		i++;
	}
	return (dest);
}

char		**ft_strndup_p(char **s, size_t n)
{
	char	**str;

	if (!(str = (char **)malloc(sizeof(char *) * (n + 1))))
		return (NULL);
	str = ft_copydup_p(str, s, n);
	str[n] = NULL;
	return (str);
}
