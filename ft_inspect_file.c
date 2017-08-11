/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inspect_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 10:47:26 by arohani           #+#    #+#             */
/*   Updated: 2017/08/11 14:23:40 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "libft/includes/libft.h"
#include <stdio.h>

int		main(int ac, char **av)
{
	int			i;
	struct stat	buf;
	
	i = 1;
	while (i < ac)
	{
		printf("Name: %s\n", av[i]);
		if (lstat(av[i], &buf) < 0)
			ft_putstr("stat error\n");
		if (S_ISREG(buf.st_mode))
			printf("Type: File\n");
		else if (S_ISDIR(buf.st_mode))
			printf("Type: Directory\n");
		else if (S_ISLNK(buf.st_mode))
			printf("Type: Symbolic Link\n");
/*		own[0] = (S_IRUSR(buf.st_mode)) ? 'r' : '-';
		own[1] = (S_IWUSR(buf.st_mode)) ? 'w' : '-';
		own[2] = (S_IXUSR(buf.st_mode)) ? 'x' : '-';
		grp[0] = (S_IRGRP(buf.st_mode)) ? 'r' : '-';
		grp[1] = (S_IWGRP(buf.st_mode)) ? 'w' : '-';
		grp[2] = (S_IXGRP(buf.st_mode)) ? 'x' : '-';
		oth[0] = (S_IROTH(buf.st_mode)) ? 'r' : '-';
		oth[1] = (S_IWOTH(buf.st_mode)) ? 'w' : '-';
		oth[2] = (S_IXOTH(buf.st_mode)) ? 'x' : '-';
*/		printf("Modes: ");
		printf((buf.st_mode & S_IRUSR) ? "r" : "-");
		printf((buf.st_mode & S_IWUSR) ? "w" : "-");
		printf((buf.st_mode & S_IXUSR) ? "x" : "-");
		printf((buf.st_mode & S_IRGRP) ? "r" : "-");
		printf((buf.st_mode & S_IWGRP) ? "w" : "-");
		printf((buf.st_mode & S_IXGRP) ? "x" : "-");
		printf((buf.st_mode & S_IROTH) ? "r" : "-");
		printf((buf.st_mode & S_IWOTH) ? "w" : "-");
		printf((buf.st_mode & S_IXOTH) ? "x" : "-");
//		printf("%s", own);
//		printf("%s", grp);
//		printf("%s", oth);
		printf("\n");
		/*		printf("value of S_ISREG is %d\n", S_ISREG(buf.st_mode));
				printf("value of S_ISDIR is %d\n", S_ISDIR(buf.st_mode));
				printf("value of S_ISLNK is %d\n", S_ISLNK(buf.st_mode));
				*/		i++;
	}
	return 0;
}
