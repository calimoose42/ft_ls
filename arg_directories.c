/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_directories.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 12:25:00 by arohani           #+#    #+#             */
/*   Updated: 2017/10/06 15:19:06 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

//after already sorting, sorted list is ready for processing
//	MAKE SURE to pass a table to this function that has applied any additional
//	option filters like -t, -a, -A, and if possible, recursive
t_dirs	*stock_dlist(char **dir)
{
	t_dirs	*head;
	t_dirs	*current;
	int 	i;

	i = 0;
	if (!(current = (t_dirs *)malloc(sizeof(t_dirs))))
		return (NULL);
	head = current;
	current->name = dir[i++];
	if (!(dir[i]))
		current->next = NULL;
	while (dir[i])
	{
		if (!(current->next = (t_dirs *)malloc(sizeof(t_dirs))))
			return (NULL);
		current = current->next;
		current->name = dir[i++];
		if (dir[i] == 0)
			current->next = NULL;
	}
	return (head);
}
/*
char	**hidden_dir_tab(char **dir, int a)
{
	int 	i;

	i = 0;
	while (dir[i] && dir[i][0] == '.')
		i++;
	dir = dir + i;
	return (dir); 
}
*/
//sort_dir_tab to apply reverse option, if necessary
char	**sort_dir_tab(char **dir, int r)
{
	int 	i;
	int 	j;
	char	*tmp;

	i = 0;
	j = 1;

	while (dir[i])
	{
		while (dir[j])
		{
			if (r == 0)
				if (ft_strcmp(dir[i], dir[j]) > 0)
				{
					tmp = dir[j];
					dir[j] = dir[i];
					dir[i] = tmp;
				}
			if (r == 1)
				if (ft_strcmp(dir[i], dir[j]) < 0)
				{
					tmp = dir[j];
					dir[j] = dir[i];
					dir[i] = tmp;
				}
			j++;
		}
		i++;
		j = i + 1;
	}
	return (dir);
}

//dir_tab to stock all directors passed as argument to separate table
//	and lists for separate processing
char	**dir_tab(char	**tab)
{
	int 		i;
	int 		j;
	struct stat	buf;
	//int 		isdir;
	char		**dir;

	i = 0;
	if (!(dir = (char **)malloc(sizeof(char *) * (dir_total(tab, 0) + 1))))
		return (NULL);
	j = 0;
	while (tab[i] != 0)
	{
		if (lstat(tab[i], &buf) < 0)
			ft_putstr("stat error\n");
		if (S_ISDIR(buf.st_mode))
		{
			if (!(dir[j] = (char *)malloc(sizeof(char) * (ft_strlen(tab[i] + 1)))))
				return (NULL);
			dir[j++] = tab[i];
		}
		i++;
	}
	dir[j] = 0;
	return (dir);
}
