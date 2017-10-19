/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inspect_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 10:47:26 by arohani           #+#    #+#             */
/*   Updated: 2017/10/19 15:39:56 by arohani          ###   ########.fr       */
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
		if (S_ISREG(buf.st_mode))		// 1) file mode
			printf("Type: File\n");
		else if (S_ISDIR(buf.st_mode))	// 1) file mode
			printf("Type: Directory\n");		//if dir and -l option, handle Total value before content display 
		//the total number of 512-byte blocks used by the files in the directory is displayed on a line by itself, 
		//immediately before the information for the files in the directory.
		else if (S_ISLNK(buf.st_mode)). // 1) file mode
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
		printf("\nNumber of links: %d\n", buf.st_nlink);	// 2) Number of links
		if ((own = getpwuid(buf.st_uid)) == NULL)			// 3) Owner Name
			printf("getpwuid error\n");
		printf("Owner: %s\n", own->pw_name);				
		if ((grp = getgrgid(buf.st_gid)) == NULL)			// 4) Group Name
			printf("getgrgid error\n");
		printf("Group: %s\n", grp->gr_name);
		printf("Size: %lld bytes\n", buf.st_size);		// 5) number of bytes in the file (handle character special / block special exceptions)
		date = ctime(&buf.st_mtime);
		while (k < 16 && j < 13)
			cleandate[j++] = date[k++];
		cleandate[j] = '\0';
		printf("Date last modified: %s\n", cleandate);	// 6) processed date
		i++;
	}
	return 0;
}
