/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 13:51:00 by arohani           #+#    #+#             */
/*   Updated: 2017/10/05 18:23:24 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

//stock_dir_content accepts a directory in form of char * and displays its content
char	**stock_dir_content(char *str)
{
	struct dirent 	*dstream;
	DIR 			*dirp;
	long int		len;
	char			**tab;

	len = 1;
	dirp = opendir(str);
	if (dirp == NULL)
	{
		ft_putstr("Cannot open directory ");
		ft_putstr(str);
		return (NULL);
	}
	while ((dstream = readdir(dirp)) != NULL)
		len++;
	if (!(tab = (char **)malloc(sizeof(char *) * len)))
		return (NULL);
	len = 0;
	closedir(dirp);
	dirp = opendir(str);
	while ((dstream = readdir(dirp)) != NULL)
	{
		if (!(tab[len] = (char *)malloc(sizeof(char) * (ft_strlen(dstream->d_name) + 1))))
			return (NULL);
		tab[len++] = dstream->d_name;
	}
	tab[len] = 0;
	closedir(dirp);
	ft_print_table(tab);
	//at this point, consider return value for sorting in -l format i.e. info file-by-file
	return (tab);
}

//stock_from_dlist takes a list of dir names and displays content of each dir separated by \n
void	stock_from_dlist(t_dirs *dlist)
{
	while (dlist)
	{
		ft_putstr(dlist->name);
		write(1, ":\n", 2);
		stock_dir_content(dlist->name);
		dlist = dlist->next;
		if (dlist)
			write(1, "\n", 1);
	}
}