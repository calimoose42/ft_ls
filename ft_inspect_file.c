/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inspect_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 10:47:26 by arohani           #+#    #+#             */
/*   Updated: 2017/08/11 16:35:35 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <time.h>
#include "libft/includes/libft.h"
#include <stdio.h>

int		main(int ac, char **av)
{
	int				i;
	struct stat		buf;
	struct passwd	*own;
	struct group	*grp;
	char			*date;
	char			cleandate[13];
	int				j;
	int				k;

	i = 1;
	j = 0;
	k = 4;
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
		printf("Modes: ");
		printf((buf.st_mode & S_IRUSR) ? "r" : "-");
		printf((buf.st_mode & S_IWUSR) ? "w" : "-");
		printf((buf.st_mode & S_IXUSR) ? "x" : "-");
		printf((buf.st_mode & S_IRGRP) ? "r" : "-");
		printf((buf.st_mode & S_IWGRP) ? "w" : "-");
		printf((buf.st_mode & S_IXGRP) ? "x" : "-");
		printf((buf.st_mode & S_IROTH) ? "r" : "-");
		printf((buf.st_mode & S_IWOTH) ? "w" : "-");
		printf((buf.st_mode & S_IXOTH) ? "x" : "-");
		printf("\nNumber of links: %d\n", buf.st_nlink);
		if ((own = getpwuid(buf.st_uid)) == NULL)
			printf("getpwuid error\n");
		printf("Owner: %s\n", own->pw_name);
		if ((grp = getgrgid(buf.st_gid)) == NULL)
			printf("getgrgid error\n");
		printf("Group: %s\n", grp->gr_name);
		printf("Size: %lld octets\n", buf.st_size);
		date = ctime(&buf.st_mtime);
		while (k < 16 && j < 13)
			cleandate[j++] = date[k++];
		cleandate[j] = '\0';
		printf("Date last modified: %s\n", cleandate);
		i++;
	}
	return 0;
}
