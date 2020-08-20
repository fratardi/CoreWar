/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_speci.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:52:54 by scoron            #+#    #+#             */
/*   Updated: 2020/05/09 13:53:33 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		cs_int(t_ftp *p, char c)
{
	p->f & F_ZERO && p->f & F_PRECI ? p->f ^= F_ZERO : 0;
	if (c == 'd' || c == 'D' || c == 'i')
	{
		p->val = ft_arg(p);
		p->size = size_nu(p, p->val);
		print_nu(p, p->val);
	}
	else
	{
		p->u_val = ft_uarg(p);
		p->size = size_ba(p, p->u_val, c);
		if (c == 'o' || c == 'O')
			print_ba(p, p->u_val, "01234567", c);
		else if (c == 'X')
			print_ba(p, p->u_val, "0123456789ABCDEF", c);
		else if (c == 'x')
			print_ba(p, p->u_val, "0123456789abcdef", c);
		else
			print_ba(p, p->u_val, "0123456789", c);
	}
}

void		cs_float(t_ftp *p, char c)
{
	long double	flt;

	(void)c;
	flt = p->f & F_LONG2 ? va_arg(p->va, long double) : va_arg(p->va, double);
	p->f & F_PRECI ? 0 : (p->preci = 6);
	p->size = size_do(p, flt);
	print_do(p, flt);
}

void		cs_char(t_ftp *p, char c)
{
	char	d[2];

	d[0] = c == '%' ? '%' : (char)va_arg(p->va, int);
	d[1] = '\0';
	p->size = 1;
	if (!(p->f & F_MINUS))
		p->f & F_ZERO ? padding(p, '0') : padding(p, ' ');
	if (d[0] == '\0')
	{
		buffer(p, -1, 0);
		write(p->fd, d, 1);
		p->retv++;
	}
	else
		buffer(p, 1, d);
	p->f & F_MINUS ? padding(p, ' ') : 0;
}

void		cs_str(t_ftp *p, char c)
{
	char	*str;
	size_t	len;

	(void)c;
	str = va_arg(p->va, char *);
	len = str ? ft_strlen(str) : 6;
	p->f & F_PRECI && p->preci < len ? len = p->preci : 0;
	p->size = len;
	if (!(p->f & F_MINUS))
		p->f & F_ZERO ? padding(p, '0') : padding(p, ' ');
	str ? buffer(p, len, str) : buffer(p, len, "(null)");
	p->f & F_MINUS ? padding(p, ' ') : 0;
}

void		cs_point(t_ftp *p, char c)
{
	unsigned long long		*point;

	(void)c;
	p->f & F_ZERO && p->f & F_PRECI ? p->f ^= F_ZERO : 0;
	p->f |= F_SHARP;
	point = (unsigned long long *)va_arg(p->va, void *);
	p->u_val = (unsigned long long)point;
	p->size = size_ba(p, p->u_val, 'x');
	p->u_val == 0 ? (p->size += 2) : 0;
	print_ba(p, p->u_val, "0123456789abcdef", 'p');
}
