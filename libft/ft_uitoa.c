/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:52:30 by scoron            #+#    #+#             */
/*   Updated: 2020/05/09 20:53:05 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_putint(char *res, unsigned long long n, size_t len)
{
	if (n == 0)
		res[0] = '0';
	while (n != 0)
	{
		res[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}

char		*ft_uitoa(unsigned long long n)
{
	char				*res;
	size_t				len;
	unsigned long long	k;

	len = 1;
	k = n;
	while (k / 10 != 0)
	{
		len++;
		k /= 10;
	}
	if (!(res = (char *)malloc((len + 1) * sizeof(char))))
		return (0);
	res[len] = 0;
	res = ft_putint(res, n, len);
	return (res);
}
