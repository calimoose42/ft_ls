/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 14:46:05 by arohani           #+#    #+#             */
/*   Updated: 2017/08/18 15:49:17 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	struct dirent		*dstream;
	DIR					*dirp;
	t_elem				*head;
	t_elem				*curr;
	struct stat			buf;
	struct passwd		*owner;
	struct group		*group;

	if (ac < 1)
		ft_putstr("Error: not enough arguments\n");
	if (!(curr = (t_elem *)malloc(sizeof(t_elem))))

	dirp = opendir("./");
	if (dirp == NULL)
	{
		ft_putstr("cannot open directory ./\n");
		return (1);
	}
	while ((dstream = readdir(dirp)) != NULL)
	{
		if (dstream->d_name[0] != '.')
		{
			ft_putstr(dstream->d_name);
			ft_putchar('\n');

	if (!(curr = (t_elem *)malloc(sizeof(t_elem))))
		ft_putstr("Error: current was not malloced\n");
	head = curr;
	curr->name = 
