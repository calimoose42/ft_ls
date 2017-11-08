/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 12:25:16 by arohani           #+#    #+#             */
/*   Updated: 2017/11/03 14:57:47 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int		main(int ac, char **av)
{
	char			**tab;
	t_opt			option = {0, 0, 0, 0, 0, 0, 0};
	int				i = 1;

	if (ac < 1)
		ft_putstr("argument error in main\n");
	while (av[i] && av[i][0] == '-')
	{	
		option = scan_options(av[i++]);
		//printf("\noption.a = %d\noption.r = %d\noption.t = %d\noption.rec = %d\noption.l = %d\n", option.a, option.r, option.t, option.rec, option.l);
	}
	if (!(av[i]))	//if no argument is passed, process separately
		dir_content_tab(".", option);
	else
	{
		tab = av + i;
		all_args(tab, option);
//		files = regular_args(all_args(tab));
	//	display_errors(arguments, option);
	//	display_regular_args(arguments, option);
	}
	return (0);
}