/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 14:57:10 by arohani           #+#    #+#             */
/*   Updated: 2017/07/26 16:20:01 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		check_stock(char **stock, char **line, int eof)
{
	char		*tmp;

	if (eof == 0 && (tmp = ft_strchr(*stock, '\n')))
	{
		*tmp = '\0';
		*line = ft_strdup(*stock);
		*stock = ft_strdup(tmp + 1);
		tmp = NULL;
		return (1);
	}
	if (eof == 1 && ft_strlen(*stock))
	{
		*line = ft_strdup(*stock);
		free(*stock);
		*stock = NULL;
		return (1);
	}
	return (0);
}

static int		check_buff(char *buff, char **stock, char **line)
{
	char		*tmp;

	if ((tmp = ft_strchr(buff, '\n')))
	{
		*tmp = '\0';
		*line = ft_strjoin(*stock, buff);
		free(*stock);
		*stock = ft_strdup(tmp + 1);
		tmp = NULL;
		free(buff);
		return (1);
	}
	return (0);
}

static char		*tmp_strjoin(char *stock, char *buff)
{
	char		*tmp;

	tmp = ft_strjoin(stock, buff);
	free(stock);
	stock = tmp;
	tmp = NULL;
	return (stock);
}

int				get_next_line(const int fd, char **line)
{
	static char	*stock = NULL;
	char		*buff;
	int			ret;

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (stock && (check_stock(&stock, line, 0)))
		return (1);
	buff = ft_strnew(BUFF_SIZE);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (check_buff(buff, &stock, line))
			return (1);
		stock = tmp_strjoin(stock, buff);
	}
	ft_strdel(&buff);
	if (ret == -1)
		return (-1);
	if (stock && (check_stock(&stock, line, 1)))
		return (1);
	return (0);
}
