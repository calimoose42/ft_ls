/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 12:25:16 by arohani           #+#    #+#             */
/*   Updated: 2017/10/11 17:41:02 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int		main(int ac, char **av)
{
	char			**tab;
	t_opt			option = {0, 0, 0, 0, 0};
	int				i = 1;

	if (ac < 1)
		ft_putstr("argument error in main\n");
	while (av[i] && av[i][0] == '-')
		option = scan_options(av[i++]);
	if (!(av[i]))	//if no argument is passed, process separately
		//sort_dir_content(stock_dir_content("."), option.r, option.a);
		return (-1);
	else
	{
		tab = av + i;
		all_args(tab, option);
	}
	return (0);
}