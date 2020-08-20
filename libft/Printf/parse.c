/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:07:22 by scoron            #+#    #+#             */
/*   Updated: 2020/05/09 12:57:51 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				parse_flags(t_ftp *p)
{
	while ((p->n = ft_strchri("# +-0", *p->format)) > -1 && ++p->format)
		p->f |= (1 << p->n);
	while (ft_isdigit(*(p->format)) && ++p->format)
		p->min = 10 * (p->min) + (*(p->format - 1) - '0');
	if (*(p->format) == '.' && ++p->format)
	{
		p->f |= F_PRECI;
		while (ft_isdigit(*(p->format)) && ++p->format)
			p->preci = 10 * (p->preci) + (*(p->format - 1) - '0');
	}
	if ((p->n = ft_strchri("hlL", *(p->format))) > -1 && ++p->format)
		p->f |= (1 << (p->n + 7));
	if ((p->n = ft_strchri("lhjz", *(p->format))) > -1 && ++p->format)
		p->f |= (1 << (p->n + 9));
	p->f & F_ZERO && p->f & F_MINUS ? p->f ^= F_ZERO : 0;
	p->f & F_SPACE && p->f & F_PLUS ? p->f ^= F_SPACE : 0;
	p->f & F_PRECI && p->preci == 0 ? p->f |= F_PREZERO : 0;
}

static void			cs_not_found(t_ftp *p, char c)
{
	(void)c;
	buffer(p, 1, p->format);
	return ;
}

static void			fill_func(void (**func)(t_ftp *p, char c))
{
	int	i;

	i = -1;
	while (++i < 256)
		func[i] = &cs_not_found;
	func['d'] = &cs_int;
	func['i'] = &cs_int;
	func['o'] = &cs_int;
	func['u'] = &cs_int;
	func['x'] = &cs_int;
	func['X'] = &cs_int;
	func['%'] = &cs_char;
	func['c'] = &cs_char;
	func['s'] = &cs_str;
	func['p'] = &cs_point;
	func['f'] = &cs_float;
}

void				parse_options(t_ftp *p)
{
	static void	(*func[256])(t_ftp *p, char c);
	char		c;

	p->min = 0;
	p->preci = 0;
	p->f = 0;
	p->val = 0;
	p->u_val = 0;
	p->size = 0;
	p->padding = 0;
	parse_flags(p);
	if (!func[0])
		fill_func(func);
	c = *(p->format);
	if ((p->n = ft_strchri("DOUCS", c)) > -1)
	{
		p->f |= F_LONG;
		c += 32;
	}
	func[(int)(c)](p, c);
}
