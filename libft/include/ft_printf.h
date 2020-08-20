/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:24:04 by scoron            #+#    #+#             */
/*   Updated: 2020/05/09 20:42:04 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>

# define BUF_SIZE 		90
# define F_SHARP		1
# define F_SPACE		2
# define F_PLUS			4
# define F_MINUS		8
# define F_ZERO			16
# define F_PREZERO		32
# define F_UPCASE		64
# define F_SHORT		128
# define F_LONG			256
# define F_LONG2		512
# define F_CHAR			1024
# define F_INTMAX		2048
# define F_SIZET		4096
# define F_PRECI		8192

typedef struct			s_ftp
{
	char				*format;
	va_list				va;
	char				*buf;
	int					fd;
	int					len_buf;
	int					n;
	int					f;
	size_t				preci;
	int					min;
	int					padding;
	int					size;
	int					retv;
	long long			val;
	unsigned long long	u_val;
}						t_ftp;

void					parse_options(t_ftp *p);
void					buffer(t_ftp *p, int n, char *str);
void					cs_int(t_ftp *p, char c);
void					cs_char(t_ftp *p, char c);
void					cs_str(t_ftp *p, char c);
void					cs_point(t_ftp *p, char c);
void					cs_float(t_ftp *p, char c);
int						ft_printf(char *format, ...);
int						ft_dprintf(int fd, char *format, ...);
void					padding(t_ftp *p, char c);
unsigned long long		ft_uarg(t_ftp *p);
long long				ft_arg(t_ftp *p);
int						size_nu(t_ftp *p, long long n);
int						size_ba(t_ftp *p, unsigned long long n, char c);
int						size_do(t_ftp *p, long double flt);
void					print_nu(t_ftp *p, long long n);
void					print_ba(t_ftp *p, unsigned long long n,
						char *base, char c);
void					print_do(t_ftp *p, long double flt);

#endif
