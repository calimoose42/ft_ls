/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 15:45:16 by arohani           #+#    #+#             */
/*   Updated: 2017/08/21 14:06:32 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft/includes/libft.h"
#include <stdio.h>

int		main(int ac, char **av)
{
	struct dirent	*dstream;	//structure to hold entire directory stream
	DIR				*dirp;		//pointer to dirstream opened later, specified by av[1]

	if (ac < 2)
	{
		ft_putstr("Usage: testprog <dirname>\n");
		return (1);
	}
	dirp = opendir(av[1]);	//dir stream initialized and pointed to by dirp
	if (dirp == NULL)
	{
		ft_putstr("Cannot open directory ");
		ft_putstr(av[1]);
		return (1);
	}
	//readdir returns a pointer to the NEXT dir entry. While !=NULL i.e. while dir entry exists
	while ((dstream = readdir(dirp)) != NULL)
	{
		if (dstream->d_name[0] != '.')	//don't show file names that start with .
		{
			ft_putstr(dstream->d_name);
			if (DT_DIR(dstream->d_type))
				printf("this file is a directory\n");
			ft_putchar('\n');
		}
	}
	closedir(dirp);	//closes and frees dir stream
	return (0);
}
