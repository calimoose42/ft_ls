/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 12:25:16 by arohani           #+#    #+#             */
/*   Updated: 2017/10/05 13:50:47 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

//dunno where to put this yet, leave it in the main for now
int 	dir_total(char **tab)
{
	int 		i;
	struct stat	buf;
	int 		isdir;

	i = 0;
	isdir = 0;
	while (tab[i] != 0)
	{
		if (lstat(tab[i], &buf) < 0)
			ft_putstr("stat error\n");
		if (S_ISDIR(buf.st_mode))
			isdir++;
		i++;
	}
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
		printf("\nFiles listed below\n");
		sort_files_tab(files_tab(tab), option.r);
		printf("\nDirectories listed below\n");
		if (dir_total(tab))
			sort_dir_tab(dir_tab(tab), option.r);
		free(tab);
	}
	return 0;
}