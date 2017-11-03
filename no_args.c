/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 13:51:00 by arohani           #+#    #+#             */
/*   Updated: 2017/11/03 15:24:54 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

//sort directory contents
char	**sort_dir_content(char **dir_data, int r, int a)
{
	int 	i;
	int 	j;
	char	*tmp;

	i = 0;
	j = 1;
	while (dir_data[i])
	{
		while (dir_data[j])
		{
			if (r == 0)
				if (ft_strcmp(dir_data[i], dir_data[j]) > 0)
				{
					tmp = dir_data[j];
					dir_data[j] = dir_data[i];
					dir_data[i] = tmp;
				}
			if (r == 1)
				if (ft_strcmp(dir_data[i], dir_data[j]) < 0)
				{
					tmp = dir_data[j];
					dir_data[j] = dir_data[i];
					dir_data[i] = tmp;
				}
			j++;
		}
		i++;
		j = i + 1;
	}
	i = 0;
	while (r == 0 && a == 0 && dir_data[i] && dir_data[i][0] == '.') //-a option if no reverse order
		i++;
	dir_data = dir_data + i;
	if (r == 1 && a == 0)
	{
		while (dir_data[i] && dir_data[i][0] != '.')
			i++;
		dir_data[i] = 0;
	}
	//ft_print_table(dir_data);
	return (dir_data);
}

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
	//at this point, consider return value for sorting in -l format i.e. info file-by-file
	return (tab);
}

//stock_from_dlist takes a list of dir names and displays content of each dir separated by \n
void	stock_from_dlist(t_dirs *dlist, int r, int a)
{
	while (dlist)
	{
		ft_putstr(dlist->name);
		write(1, ":\n", 2);
		sort_dir_content(stock_dir_content(dlist->name), r, a);
		dlist = dlist->next;
		if (dlist)
			write(1, "\n", 1);
	}
}