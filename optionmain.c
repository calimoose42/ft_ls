/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optionmain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 14:26:12 by arohani           #+#    #+#             */
/*   Updated: 2017/08/22 15:25:39 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	char 		*str;
	t_opt		option = {0, 0, 0, 0, 0};
	int			i;

	str = "./";
	i = 0;
	if (av[1])
	{
		while (av[1][i] && ac > 1)
		{
			if (av[1][0] != '-')
			{
				ft_putstr("Error: no hyphen in second argument\n");
				exit(1);
			}
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
	if ((ac == 1 || (av[1] && av[1][0] == '-')) && !(ac > 2))
		list_dir(str, option.a);
	return (0);
}
