/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 11:44:17 by scoron            #+#    #+#             */
/*   Updated: 2020/05/18 05:59:23 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int		i;
	long	result;
	int		sign;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
			|| str[i] == '\r' || str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = 10 * result + str[i] - '0';
		i++;
	}
	return (sign * (int)result);
}

int			ft_is_not_value(char *numb, int value)
{
	char *val_str;

	while (*numb == '\n' || *numb == '\v' || *numb == '\f'
		|| *numb == '\r' || *numb == '\t' || *numb == ' ')
		numb++;
	if (*numb == '+')
		numb++;
	val_str = ft_itoa(value);
	if (ft_strcmp(numb, val_str))
		return (1);
	return (0);
}

int			ft_no_numb(char *numb)
{
	int i;

	i = 0;
	while (numb[i] == '\n' || numb[i] == '\v' || numb[i] == '\f'
		|| numb[i] == '\r' || numb[i] == '\t' || numb[i] == ' ')
		i++;
	if (numb[i] == '+' || numb[i] == '-')
		i++;
	while (numb[i])
	{
		if (numb[i] >= '0' && numb[i++] <= '9')
			return (0);
	}
	return (1);
}

int			ft_atoi_err(const char *str, int e)
{
	int				i;
	long long int	result;
	long long int	sign;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
			|| str[i] == '\r' || str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		sign = (str[i++] == '-' ? -1 : 1);
	if (str[i] < '0' || str[i] > '9')
		return (e);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > 214748364)
			return (e);
		if (result == 214748364 && ((sign == 1 && str[i] == '8')
									|| str[i] == '9'))
			return (e);
		result = 10 * result + str[i++] - '0';
	}
	return ((int)(sign * result));
}

int			ft_atoi_er(const char *str)
{
	int					i;
	long long int		result;
	long long int		sign;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		sign = (str[i++] == '-' ? -1 : 1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > 214748364)
			return (sign == -1 ? 0 : -1);
		if (result == 214748364 && ((sign == 1 && str[i] == '8')
									|| str[i] == '9'))
			return (sign == -1 ? 0 : -1);
		result = 10 * result + str[i++] - '0';
	}
	return ((int)(sign * result));
}
