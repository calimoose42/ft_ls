/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 12:25:16 by arohani           #+#    #+#             */
/*   Updated: 2017/11/28 15:18:36 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int		main(int ac, char **av)
{
	char			**tab;
	t_opt			option = {NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int				i = 1;
//	t_files			*files = NULL;

	if (ac < 1 || ft_strcmp(av[0], "./ft_ls"))
	{
		ft_putstr("not enough arguments or incorrect executable specified\n");
		exit (-1);
	}
	while (av[i] && av[i][0] == '-')
	{
		if (!(ft_strcmp(av[i], "--")))	//handles '--' option-ender
		{
			i++;
			break;
		}
		option = scan_options(av[i++]);
		//printf("\noption.a = %d\noption.r = %d\noption.t = %d\noption.rec = %d\noption.l = %d\n", option.a, option.r, option.t, option.rec, option.l);
	}
	if (!(av[i]))	//if no argument is passed, process separately
		dir_content_tab(".", option);
	else
	{
		tab = av + i;
		option.R_args = 1;
		all_args(tab, option);
//		files = regular_args(all_args(tab));
	//	display_errors(arguments, option);
	//	display_regular_args(arguments, option);
	}
	return (0);
}
