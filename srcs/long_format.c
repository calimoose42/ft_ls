/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 17:00:58 by arohani           #+#    #+#             */
/*   Updated: 2017/11/03 18:08:30 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

t_opt		dir_block_size(t_files *list, t_opt option)
{
	while (list)
	{
		if (list->name[0] == '.')
			list = list->next;
		option.block += (long)(list->buf).st_blocks;
		list = list->next;
	}
	return (option);
}

int			digits(int n)
{
	int		count;

	count = 0;
	if (n == 0)
		count = 1;
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

int			column_size(t_files *list, int link)
{
	int		max;
	int		dig;

	max = 0;
	dig = 0;
	while (list && link == 1)
	{
		max = ((int)list->buf.st_nlink) > max ? (int)list->buf.st_nlink : max;
		list = list->next;
	}
	while (list && link == 0)
	{
		max = ((int)list->buf.st_size) > max ? (int)list->buf.st_size : max;
		list = list->next;
	}
	if (max == 0)
		dig = 1;
	while (max > 0)
	{
		dig++;
		max /= 10;
	}
	return (dig);
}

void		long_format(t_files *list, t_opt option)
{
	t_files		*head = NULL;
	int			i;
	int			j;
	int			k;
	int			max = 0;
	int			max2 = 0;

	head = list;
	max = column_size(head, 1);
	max2 = column_size(head, 0);
	if (list && list->error != 1 && option.file == 2)
	{
		ft_putstr("total ");
		ft_putnbr(option.block);
		ft_putchar('\n');
	}
	while (list && list->error != 1 && option.file > 0)
	{
		i = 0;
		j = 0;
		k = 4;
		if (list && i == 0)
		{
			(list->perm[i]) = 
				(S_ISFIFO(list->buf.st_mode)) ? 'p' :
				(S_ISCHR(list->buf.st_mode)) ? 'c' :
				(S_ISDIR(list->buf.st_mode)) ? 'd' :
				(S_ISBLK(list->buf.st_mode)) ? 'b' :
				(S_ISREG(list->buf.st_mode)) ? '-' :
				(S_ISLNK(list->buf.st_mode)) ? 'l' :
				's';
			if (list->perm[i] == 's' && !(S_ISSOCK(list->buf.st_mode)))
			{
				ft_putstr("Error in long format permissions\n");
				exit (-1);
			}
			i++;
		}
		while (i < 10)
		{
			list->perm[1] = (list->buf.st_mode & S_IRUSR) ? 'r' : '-';
			list->perm[2] = (list->buf.st_mode & S_IWUSR) ? 'w' : '-';
			list->perm[3] = (list->buf.st_mode & S_IXUSR) ? 'x' : '-';
			list->perm[4] = (list->buf.st_mode & S_IRGRP) ? 'r' : '-';
			list->perm[5] = (list->buf.st_mode & S_IWGRP) ? 'w' : '-';
			list->perm[6] = (list->buf.st_mode & S_IXGRP) ? 'x' : '-';
			list->perm[7] = (list->buf.st_mode & S_IROTH) ? 'r' : '-';
			list->perm[8] = (list->buf.st_mode & S_IWOTH) ? 'w' : '-';
			list->perm[9] = (list->buf.st_mode & S_IXOTH) ? 'x' : '-';
			//need to also check S, s before x, -, or stickies
			i = 10;
		}
		list->perm[i] = '\0';
		//NEED TO MANAGE @ or + additional symbol for permissions (bonus)
		// https://stackoverflow.com/questions/36229265/how-to-get-extended-attributes-of-a-fileunix-c for '@' & '+'
		// deal with directory being readable or not before using it, i.e. error "ls: no_perm: Permission denied"
		ft_putstr(list->perm);
		ft_nputchar(' ', (2 + (max - digits((int)list->buf.st_nlink))));
		ft_putstr(ft_itoa((int)list->buf.st_nlink));
		write (1, " ", 1);
		if ((list->own = getpwuid(list->buf.st_uid)) == NULL)
			ft_putstr("error getting user name\n");
		else
			ft_putstr(list->own->pw_name);
		write (1, "  ", 2);		//should be 2 from the HIGHEST NUMBER in column (i.e. update max_dig in while loop at each turn)
		if ((list->group = getgrgid(list->buf.st_gid)) == NULL)
			ft_putstr("error getting group name\n");
		else
			ft_putstr(list->group->gr_name);
		//write (1, "  ", 2);		//should be 2 from the HIGHEST NUMBER in column (i.e. update max_dig in while loop at each turn)
		ft_nputchar(' ', (2 + (max2 - digits((int)list->buf.st_size))));
		ft_putstr(ft_itoa((int)list->buf.st_size));
		write (1, " ", 1);
		list->raw_date = ft_strdup(ctime(&list->buf.st_mtime));
		while (k < 16 && j < 13)
			list->cleandate[j++] = list->raw_date[k++];
		list->cleandate[j] = '\0';
		ft_putstr(list->cleandate);
		write (1, " ", 1);
		ft_putstr(list->name);
		write(1, "\n", 1);
		list = list->next;
	}
	if (option.file == 0)
		write(1, "\n", 1);
	while (list && option.file == 0)
	{
		ft_putstr(list->name);
		ft_putstr(":\n");
		ft_putstr("total ");
		ft_putnbr(option.block);
		ft_putchar('\n');
		dir_content_tab(list->name, option);
		if (list->next)
			write(1, "\n", 1);
		list = list->next;
	}	
	if (option.l != 1)
		ft_putstr("in long_format without l option\n");
	return ;
}