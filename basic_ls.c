/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 10:47:26 by arohani           #+#    #+#             */
/*   Updated: 2017/10/04 16:59:30 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
*/
#include "ft_ls.h"
#include <stdio.h>

char	**sort_files(char **files, int r)
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
	printf("after sorting, file order is as follows : \n");
	ft_print_table(files);
	return (files);
}

char	**files(char **tab)
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

char	**directories(char	**tab)
{
	int i;
	int j;
	struct stat	buf;
	int isdir;
	char	**dir;

	i = 0;
	isdir = 0;
	while (tab[i] != 0)
	{
		if (lstat(tab[i], &buf) < 0)
			ft_putstr("stat error\n");
		if (S_ISDIR(buf.st_mode))
			isdir++;
		i++;
	}
	if (!(dir = (char **)malloc(sizeof(char *) * (isdir + 1))))
		return (NULL);
	isdir = 0;
	i = 0;
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

int		main(int ac, char **av)
{
	char			**tab;
	t_opt			option = {0, 0, 0, 0, 0};
	int				i = 1;
	int				j = 1;
// gonna try and store command line arguments in 2d array without ls options 
	if (!(tab = (char **)malloc(sizeof(char *) * (ac))))
		return (-1);
	if (av[1] && av[1][0] == '-')
	{
		while (av[1][j] != '\0')
		{
			option.l = (av[1][j] != 'l' && option.l == 0) ? 0 : 1;
			option.rec = (av[1][j] != 'R' && option.rec == 0) ? 0 : 1;
			option.t = (av[1][j] != 't' && option.t == 0) ? 0 : 1;
			option.r = (av[1][j] != 'r' && option.r == 0) ? 0 : 1;
			option.a = (av[1][j] != 'a' && option.a == 0) ? 0 : 1;
			j++;
		}
		i++;
	}
	j = 0;
	while (av[i])
	{
		if (!(tab[j] = (char *)malloc(sizeof(char) * (ft_strlen(av[i] + 1)))))
			return (-1);
		tab[j++] = av[i++];
	}
	tab[j] = 0;

//	is_dir(tab);, while is_dir == 0, store files in struct or table, to store and display
//	while is_dir == 1, store into struct or table, to later store and display recursively if necessary
	directories(tab);
	sort_files(files(tab), option.r);
	free(tab);
	return 0;
}	

/*	int				i;
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
} */
