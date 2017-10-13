/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 12:24:45 by arohani           #+#    #+#             */
/*   Updated: 2017/10/12 20:39:13 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

//after already sorting, sorted list is ready for processing
//	MAKE SURE to pass a table to this function that has applied any additional
//	option filters like -t, -a, -A, and if possible, recursive
t_files	*stock_flist(char **files)
{
	t_files	*head;
	t_files	*current;
	int 	i;

	i = 0;
	if (!(current = (t_files *)malloc(sizeof(t_files))))
		return (NULL);
	head = current;
	current->name = files[i++];
	if (!(files[i]))
		current->next = NULL;
	while (files[i])
	{
		if (!(current->next = (t_files *)malloc(sizeof(t_files))))
			return (NULL);
		current = current->next;
		current->name = files[i++];
		if (files[i] == 0)
			current->next = NULL;
	}
	while (head)
	{
		ft_putstr(head->name);
		write(1, "\n", 1);
		head = head->next;
	}
	return (head);
}

//rename later. Currently only applies -r sorting, if necessary
char	**sort_files_tab(char **files, int r)
{
	int 	i;
	int 	j;
	char	*tmp;

	i = 0;
	j = 1;

	while (files[i])
	{
		while (files[j])
		{
			if (r == 0)
				if (ft_strcmp(files[i], files[j]) > 0)
				{
					tmp = files[j];
					files[j] = files[i];
					files[i] = tmp;
				}
			if (r == 1)
				if (ft_strcmp(files[i], files[j]) < 0)
				{
					tmp = files[j];
					files[j] = files[i];
					files[i] = tmp;
				}
			j++;
		}
		i++;
		j = i + 1;
	}
	stock_flist(files);
	return (files);
}

//to store all files passed as argument into separate table for separate processing
char	**files_tab(char **tab)
{
	int i;
	int j;
	struct stat	buf;
	int isfile;
	char	**files;

	i = 0;
	isfile = 0;
	while (tab[i] != 0)
	{
		if (lstat(tab[i], &buf) < 0)
			ft_putstr("stat error\n");
		if (S_ISREG(buf.st_mode) || S_ISLNK(buf.st_mode))
			isfile++;
		i++;
	}
	if (!(files = (char **)malloc(sizeof(char *) * (isfile + 1))))
		return (NULL);
	isfile = 0;
	i = 0;
	j = 0;
	while (tab[i] != 0)
	{
		if (lstat(tab[i], &buf) < 0)
			ft_putstr("stat error\n");
		if (S_ISREG(buf.st_mode) || S_ISLNK(buf.st_mode))
		{
			if (!(files[j] = (char *)malloc(sizeof(char) * (ft_strlen(tab[i] + 1)))))
				return (NULL);
			files[j++] = tab[i];
			isfile++;
		}
		i++;
	}
	files[j] = 0;
	return (files);
}