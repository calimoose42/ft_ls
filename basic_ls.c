/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 10:47:26 by arohani           #+#    #+#             */
/*   Updated: 2017/10/04 19:09:26 by arohani          ###   ########.fr       */
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

t_dirs	*stock_dlist(char **dir, int no_args)
{
	t_dirs	*head;
	t_dirs	*current;
	int 	i;

	i = 0;
	if (!(current = (t_dirs *)malloc(sizeof(t_dirs))))
		return (NULL);
	head = current;
	if (no_args == 1)
	{
		current->name = ".";
		current->next = NULL;
		return (head);
	}
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
	while (head)
	{
		ft_putstr(head->name);
		write(1, "\n", 1);
		head = head->next;
	}
	return (head);
}

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
	stock_dlist(dir, 0);
	return (dir);
}

char	**dir_tab(char	**tab)
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
	if (isdir != 0)
	{
		if (!(dir = (char **)malloc(sizeof(char *) * (isdir + 1))))
			return (NULL);
	}
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

t_opt	scan_options(char *str)
{
	int 	i;
	t_opt	option = {0, 0, 0, 0, 0};

	i = 1;
	while (str[i])
	{
		option.l = (str[i] != 'l' && option.l == 0) ? 0 : 1;
		option.rec = (str[i] != 'R' && option.rec == 0) ? 0 : 1;
		option.t = (str[i] != 't' && option.t == 0) ? 0 : 1;
		option.r = (str[i] != 'r' && option.r == 0) ? 0 : 1;
		option.a = (str[i] != 'a' && option.a == 0) ? 0 : 1;
		i++;
	}
	return (option);
}
/*
char	**current_dir(int empty)
{
	char	**tab;

	if (!(tab = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	if (!(tab[0] = (char *)malloc(sizeof(char) * 2)))
		return (NULL);
	tab[0][0] = '.';
	tab[0][1] = '\0';
	if (!(tab[1] = (char *)malloc(sizeof(char) * 1)))
		return (NULL);
	tab[1][0] = 0;
	return (tab);
}
*/
int		main(int ac, char **av)
{
	char			**tab;
	t_opt			option = {0, 0, 0, 0, 0};
	int				i = 1;
	int				j = 0;

	if (!(tab = (char **)malloc(sizeof(char *) * (ac))))
		return (-1);
	if (av[1] && av[1][0] == '-')
	{
		option = scan_options(av[1]);
		i++;
	}
	if (av[i])
	{
		if (!(tab = (char **)malloc(sizeof(char *) * (ac))))
			return (-1);
		while (av[i])
		{
			if (!(tab[j] = (char *)malloc(sizeof(char) * (ft_strlen(av[i] + 1)))))
				return (-1);
			tab[j++] = av[i++];
		}
	}
	if (ac == 1 || (ac == 2 && av[1][0] == '-'))
	{
		tab[j] = "noarg";
		stock_dlist(tab, 1);
	}
//	is_dir(tab);, while is_dir == 0, store files in struct or table, to store and display
//	while is_dir == 1, store into struct or table, to later store and display recursively if necessary
	else
	{
		tab[j] = 0;
		printf("\nFiles listed below\n");
		sort_files_tab(files_tab(tab), option.r);
		printf("\nDirectories listed below\n");
		sort_dir_tab(dir_tab(tab), option.r);
		free(tab);
	}
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
