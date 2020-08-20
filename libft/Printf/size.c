/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 17:05:45 by scoron            #+#    #+#             */
/*   Updated: 2020/05/09 13:54:47 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		size_nu(t_ftp *p, long long n)
{
	int			size;
	int			len;
	int			pre;

	size = p->f & F_PREZERO && !(n) ? 0 : 1;
	size += p->f & F_SPACE || p->f & F_PLUS || p->val < 0 ? 1 : 0;
	len = 1;
	pre = p->preci;
	while (n / 10 != 0 && ++size && ++len)
		n /= 10;
	while (pre-- > len)
		size++;
	return (size);
}

int		size_ba(t_ftp *p, unsigned long long n, char c)
{
	int			size;
	int			bs;
	int			len;
	int			pre;

	size = p->f & F_PREZERO && !(n) ? 0 : 1;
	pre = p->preci;
	bs = 10;
	len = 1;
	if (c == 'o' || c == 'x' || c == 'X')
		bs = c == 'o' ? 8 : 16;
	if (p->f & F_SHARP && (c == 'x' || c == 'X'))
		size += p->u_val ? 2 : 0;
	if (p->f & F_SHARP && c == 'o')
		size += p->u_val ? 1 && ++len : 0;
	while (n / bs != 0 && ++size && ++len)
		n /= bs;
	while (pre-- > len)
		size++;
	return (size);
}

int		size_do(t_ftp *p, long double flt)
{
	int			size;
	long long	itg;
	int			len;

	size = p->f & F_SPACE || p->f & F_PLUS || flt < 0 ? 2 : 1;
	len = 1;
	itg = (long long)flt;
	while (itg / 10 != 0 && ++size && ++len)
		itg /= 10;
	size += p->preci == 0 && !(p->f & F_SHARP) ? 0 : p->preci + 1;
	return (size);
}
