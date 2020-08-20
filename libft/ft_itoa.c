/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:52:30 by scoron            #+#    #+#             */
/*   Updated: 2020/05/09 13:43:23 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_putint(char *res, long long n, size_t len)
{
	unsigned long long	tmp;

	if (n == 0)
		res[0] = '0';
	tmp = n < 0 ? -n : n;
	if (n < 0)
		res[0] = '-';
	while (tmp != 0)
	{
		res[--len] = (tmp % 10) + '0';
		tmp /= 10;
	}
	return (res);
}

char		*ft_itoa(long long n)
{
	char		*res;
	size_t		len;
	long long	k;

	len = 1;
	k = n;
	if (n < 0)
		len++;
	while (k / 10 != 0 && len++)
		k /= 10;
	if (!(res = (char *)malloc((len + 1) * sizeof(char))))
		return (0);
	res[len] = 0;
	res = ft_putint(res, n, len);
	return (res);
}
