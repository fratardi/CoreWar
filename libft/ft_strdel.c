/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 16:11:18 by scoron            #+#    #+#             */
/*   Updated: 2020/05/09 20:52:10 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strdel(char **as)
{
	if (as != NULL)
	{
		if (*as != NULL)
			free(*as);
		*as = NULL;
	}
}

void	ft_strlst_free(char **strlst)
{
	int	i;

	i = -1;
	if (strlst == NULL)
		return ;
	while (strlst[++i] != NULL)
		free(strlst[i]);
	free(strlst);
}
