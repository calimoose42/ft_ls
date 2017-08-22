/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optionmain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 14:26:12 by arohani           #+#    #+#             */
/*   Updated: 2017/08/22 16:45:00 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int		main(int ac, char **av)
{
	char 		*str;
	t_opt		option = {0, 0, 0, 0, 0};
	int			i;

	str = (av[1] && av[1][0] != '-') ? av[1] : "./";
	i = 0;
	if (av[1] && av[1][0] == '-')
	{
		while (av[1][i] && ac > 1)
		{
			if (av[1][i] == 'l')
				option.l = 1;
			if (av[1][i] == 'r')
				option.r = 1;
			if (av[1][i] == 'R')
				option.rec = 1;
			if (av[1][i] == 't')
				option.t = 1;
			if (av[1][i] == 'a')
				option.a = 1;
			i++;
		}
	}
	if (ac == 1)
	{
		list_dir("./", option.a);
		return (0);
	}
	i = (av[1][0] == '-') ? 2 : 1;
	while (av[i])
	{
		if ((ac > 2 && av[1][0] != '-') || (ac > 3 && av[1][0] == '-'))
		{
			ft_putstr(av[i]);
			ft_putstr(":\n");
		}
		list_dir(av[i++], option.a);
		if (av[i])
			ft_putchar('\n');
	}
	return (0);
}
