/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 12:25:16 by arohani           #+#    #+#             */
/*   Updated: 2017/10/06 17:52:13 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int		is_dir(char *str)
{
	struct stat buf;
	if (str)
	{
		if (lstat(str, &buf) < 0)
			ft_putstr("stat error\n");
		if (S_ISDIR(buf.st_mode))
			return (1);
	}
	return (0);
}

//dunno where to put this yet, leave it in the main for now
int 	dir_total(char **tab, int file_check)
{
	int 		i;
	struct stat	buf;
	int 		isdir;
	int 		isfile;

	i = 0;
	isfile = 0;
	isdir = 0;
	while (tab[i] != 0)
	{
		if (lstat(tab[i], &buf) < 0)
			ft_putstr("stat error\n");
		if (S_ISDIR(buf.st_mode))
			isdir++;
		if (S_ISREG(buf.st_mode) || S_ISLNK(buf.st_mode))
			isfile++;
		i++;
	}
	if (file_check == 1)
		return (isfile);
	return (isdir);
}

int		main(int ac, char **av)
{
	char			**tab;
	char			**processed;
	t_dirs			*pro;
	t_opt			option = {0, 0, 0, 0, 0};
	int				i = 1;

	if (av[1] && av[1][0] == '-')
	{
		option = scan_options(av[1]);
		i++;
	}
	if (ac == 1 || (ac == 2 && av[1][0] == '-'))
		sort_dir_content(stock_dir_content("."), option.r, option.a);
	if (!(ac == 1 || (ac == 2 && av[1][0] == '-')))
	{
		tab = av + i;
		if (dir_total(tab, 1))	//1 value checks for files to store separately
		{
			sort_files_tab(files_tab(tab), option.r);
			write(1, "\n", 1);
		}
		if (dir_total(tab, 0))
		{
			processed = sort_dir_tab(dir_tab(tab), option.r);
			pro = stock_dlist(processed, option.t, option.r);
			stock_from_dlist(pro, option.r, option.a);
			//stock_from_dlist((stock_dlist((sort_dir_tab(dir_tab(tab), option.r), option.t, option.r)), option.r, option.a));
		}
	}
	return 0;
}