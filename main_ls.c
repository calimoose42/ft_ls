/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 12:25:16 by arohani           #+#    #+#             */
/*   Updated: 2017/10/05 16:39:00 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

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
	t_opt			option = {0, 0, 0, 0, 0};
	int				i = 1;
	int				j = 0;

	if (!(tab = (char **)malloc(sizeof(char *) * (ac))))
		return (-1);
	if (av[1] && av[1][0] == '-')
	{
		option = scan_options(av[1]);
		i++;
	}
	if (av[i])
	{
		if (!(tab = (char **)malloc(sizeof(char *) * (ac))))
			return (-1);
		while (av[i])
		{
			if (!(tab[j] = (char *)malloc(sizeof(char) * (ft_strlen(av[i] + 1)))))
				return (-1);
			tab[j++] = av[i++];
		}
	}
	tab[j] = 0;
	if (ac == 1 || (ac == 2 && av[1][0] == '-'))
		stock_dir_content(".");
//	is_dir(tab);, while is_dir == 0, store files in struct or table, to store and display
//	while is_dir == 1, store into struct or table, to later store and display recursively if necessary
	else
	{
		if (dir_total(tab, 1))
			sort_files_tab(files_tab(tab), option.r);
		write(1, "\n", 1);
		if (dir_total(tab, 0))
			sort_dir_tab(dir_tab(tab), option.r);
		free(tab);
	}
	return 0;
}
