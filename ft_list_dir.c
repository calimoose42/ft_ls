/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 15:45:16 by arohani           #+#    #+#             */
/*   Updated: 2017/08/10 16:07:27 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft/includes/libft.h"

int		main(int ac, char **av)
{
	struct dirent	*pDirent;
	DIR				*pDir;

	if (ac < 2)
	{
		ft_putstr("Usage: testprog <dirname>\n");
		return (1);
	}
	pDir = opendir(av[1]);
	if (pDir == NULL)
	{
		ft_putstr("Cannot open directory ");
		ft_putstr(av[1]);
		return (1);
	}
	while ((pDirent = readdir(pDir)) != NULL)
	{
		if (pDirent->d_name[0] != '.')
		{
			ft_putstr(pDirent->d_name);
			ft_putchar('\n');
		}
	}
	closedir(pDir);
	return (0);
}
