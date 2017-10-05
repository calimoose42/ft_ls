/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 13:51:00 by arohani           #+#    #+#             */
/*   Updated: 2017/10/05 15:36:02 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

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
		printf("tab should be stocked with : %s\n", dstream->d_name);
		printf("tab value is : %s\n", tab[len]);
	}
	tab[len] = 0;
	closedir(dirp);
	printf("here is the table of dir contents : \n");
	ft_print_table(tab);
	return (tab);
}