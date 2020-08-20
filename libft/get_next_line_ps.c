/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_ps.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 17:54:28 by scoron            #+#    #+#             */
/*   Updated: 2020/05/09 21:06:43 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_joinfree_ps(char *res, int fd, int *checkread)
{
	char	*buf;
	char	*tmp;

	*checkread = 1;
	tmp = 0;
	if (!(buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (NULL);
	*buf = 0;
	while (!(ft_strchr(buf, '\n')) && *checkread > 0)
	{
		if ((*checkread = read(fd, buf, BUFF_SIZE)) >= 0)
		{
			buf[*checkread] = '\0';
			if (!res)
				tmp = ft_strdup(buf);
			else
				tmp = ft_strjoin(res, buf);
			free(res);
			res = tmp;
		}
	}
	free(buf);
	*checkread = (res && *res && checkread >= 0) ? 1 : *checkread;
	return (res);
}

char			findlastchar(char *res, char lastchar)
{
	char		last;

	if (res == NULL && lastchar == '\0')
		return ('\n');
	if (*res == '\0')
		return (lastchar);
	while (*res)
	{
		last = *res;
		res++;
	}
	return (last);
}

char			*ft_check_if_join(char *res, int fd, int *checkread)
{
	if (res == NULL)
		return (ft_joinfree_ps(res, fd, checkread));
	else if (!(ft_strchr(res, '\n')))
		return (ft_joinfree_ps(res, fd, checkread));
	else
		return (res);
}

int				get_next_line_ps(const int fd, char **line)
{
	static char		*res;
	int				*checkread;
	int				i;
	static char		lastchar = 0;

	i = 1;
	checkread = &i;
	lastchar = findlastchar(res, lastchar);
	if (fd < 0 || line == NULL || BUFF_SIZE <= 0)
	{
		res != NULL ? free(res) : 0;
		return (-1);
	}
	res = ft_check_if_join(res, fd, checkread);
	if (*checkread < 0)
	{
		res != NULL ? free(res) : 0;
		return (-1);
	}
	lastchar = findlastchar(res, lastchar);
	*checkread = (*checkread == 0 && lastchar != '\n') ? -1 : *checkread;
	*line = ft_strcutuntil(&res, '\n');
	(*checkread <= 0 && res != NULL) ? free(res) : 0;
	return (*checkread > 0 ? 1 : *checkread);
}
