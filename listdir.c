/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 15:45:16 by arohani           #+#    #+#             */
/*   Updated: 2017/08/22 15:19:43 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int		list_dir(char *str, int a)
{
	struct dirent	*dstream;	//structure to hold entire directory stream
	DIR				*dirp;		//pointer to dirstream opened later, specified by av[1]

	dirp = opendir(str);	//dir stream initialized and pointed to by dirp
	if (dirp == NULL)
	{
		ft_putstr("Cannot open directory ");
		ft_putstr(str);
		return (1);
	}
	//readdir returns a pointer to the NEXT dir entry. While !=NULL i.e. while dir entry exists
	while ((dstream = readdir(dirp)) != NULL)
	{
		if (dstream->d_name[0] != '.' && a == 0)	//don't show file names that start with .
		{
			ft_putstr(dstream->d_name);
			ft_putchar('\n');
		}
		if (a == 1)
		{
			ft_putstr(dstream->d_name);
			ft_putchar('\n');
		}
	}
	closedir(dirp);	//closes and frees dir stream
	return (0);
}
