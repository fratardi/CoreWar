/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 13:07:29 by scoron            #+#    #+#             */
/*   Updated: 2019/03/13 20:31:38 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (ft_strlen(s1) > ft_strlen(s2))
		return (ft_strncmp(s1, s2, (ft_strlen(s1))));
	return (ft_strncmp(s1, s2, (ft_strlen(s2))));
}
