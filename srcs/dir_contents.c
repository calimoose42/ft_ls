/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_contents.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 14:09:55 by arohani           #+#    #+#             */
/*   Updated: 2017/11/03 17:45:04 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

t_files		*dir_recursive(t_files *sub_dirs, t_opt option) 	//handles recursive after displaying 
{
	t_files		*sorted = NULL;
//	t_files		*head = NULL;

//	sorted = dir_args(head, option); //should have sorted list of directories within analyzed directory, need to
	option.R_par = (option.R_par == NULL) ? sub_dirs : option.R_par;
	if (sub_dirs != NULL)
		sorted = (option.t == 1) ? time_sort_list(sub_dirs, option) : reverse_lex(sub_dirs, option);
	else if (option.R_par->next != NULL)
	{	
		option.R_par = option.R_par->next;
		sub_dirs = option.R_par;
		sorted = (option.t == 1) ? time_sort_list(sub_dirs, option) : reverse_lex(sub_dirs, option);
	}
	else
		return (NULL);
	printf("DEBUG 1\n");
	print_list(sorted);
	while (sorted)
	{
		printf("DEBUG 2\n");
		display_directories(sorted, option);
		sorted = sorted->next;
	}
/*	head = head->next;
	if (head)
	{
		printf("DEBUG 3A\n");
		sorted = (option.t == 1) ? time_sort_list(head, option) : reverse_lex(head, option);
		printf("head is now = to \n");
		print_list(head);
	}
*/	return (NULL);
}

t_files		*dir_content_list(char **tab, t_opt option, char *str)
{
	int 		i;
	t_files		*head = NULL;
	t_files 	*current = NULL;
	t_files		*sub_dir = NULL;
	t_files		*sub_head = NULL;

	i = 0;
	option.parent = ft_strjoin(str, "/");
//	printf("DEBUG 7\n");
	while (tab[i] && option.a == 0 && tab[i][0] == '.')
		i++;
	if (!(tab[i]))
		return (NULL);
	if (!(current = (t_files *)malloc(sizeof(t_files))))
		return (NULL);
	head = current;
	current->name = ft_strdup(tab[i++]);
	current->path = ft_strdup(option.parent);
	current->error = (lstat(ft_strjoin(current->path, current->name), &current->buf) < 0) ? 1 : 0;
	printf("current->name = %s\ncurrent->path = %s\ncurrent->error = %d\n", current->name, current->path, current->error);
	current->next = NULL;
//	printf("DEBUG 8\n");
	//if (current)
	//	printf("current->name = %s\n", current->name);
	if (S_ISDIR(current->buf.st_mode))
	{	
		printf("DEBUG DIR 1\n");
//		printf("DEBUG 9\n");
		if (!(sub_dir = (t_files *)malloc(sizeof(t_files))))
			return (NULL);
		sub_dir->name = ft_strdup(current->name);
		sub_dir->buf = current->buf;
		sub_dir->path = ft_strdup(current->path);
		sub_dir->next = NULL;
		sub_head = sub_dir;
	}
	while (tab[i])
	{
		printf("DEBUG 10\n");
//		printf("file name = %s\n", tab[i]);
		while (option.a == 0 && tab[i][0] == '.')
			i++;
		if (!(current->next = (t_files *)malloc(sizeof(t_files))))
			return (NULL);
		current = current->next;
		current->name = ft_strdup(tab[i++]);
		current->path = ft_strdup(option.parent);
		current->error = (lstat(ft_strjoin(current->path, current->name), &current->buf) < 0) ? 1 : 0;
		printf("current->path = %s\ncurrent->name = %s\ncurrent->error = %d\n", current->path, current->name, current->error);
		if (S_ISDIR(current->buf.st_mode))		//creating list of all sub-directories
		{	
//			printf("DEBUG 11\n");
			printf("DEBUG DIR 2\n");
			if (!(sub_head))
			{
	//			printf("DEBUG no sub_head\n");
				if (!(sub_dir = (t_files *)malloc(sizeof(t_files))))
					return (NULL);
				sub_dir->name = ft_strdup(current->name);
				sub_dir->buf = current->buf;
				sub_dir->path = ft_strdup(current->path);
				//sub_dir->next = NULL;
				sub_head = sub_dir;
			}
			else 
			{
	//			printf("dir_content_list DEBUG 3\n");
				if (!(sub_dir->next = (t_files *)malloc(sizeof(t_files))))
					return (NULL);
				sub_dir = sub_dir->next;
				sub_dir->name = ft_strdup(current->name);
				sub_dir->buf = current->buf;
				sub_dir->path = ft_strdup(current->path);
				//sub_dir->next = NULL;
			}
		}
		printf("DEBUG 12\n");
		if (tab[i] == 0)
		{
			if (sub_dir != NULL)
				sub_dir->next = NULL;
			current->next = NULL;
		}
	}
//	printf("sub_head should be : \n");
//	print_list(sub_head);
//	printf("DEBUG 13\n");
	option = dir_block_size(head, option);
	option = check_combo(head, option);
	if (option.rec == 1)
	{
		printf("feeding recursively into dir_recursive\n");
		if (!(sub_head))
			printf("sub_head is NULL, feeding to dir_recursive\n");
		dir_recursive(sub_head, option);
	}
	else if (head)
		(option.t == 1) ? time_sort_list(head, option) : reverse_lex(head, option);
	return (head);
}

t_files		*dir_content_tab(char *str, t_opt option)
{
	struct dirent 	*dstream;
	DIR 			*dirp = NULL;
	long int		len;
	char			**tab = NULL;
	t_files			*dir_content;

	len = 1;
	dirp = opendir(str);
//	printf("DEBUG 1\n");
	if (dirp == NULL)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(str);
		ft_putstr(": Permission denied\n");
		return (NULL);
	}
//	printf("DEBUG 2\n");
	while ((dstream = readdir(dirp)) != NULL)
		len++;
//	printf("DEBUG 3\n");
	if (!(tab = (char **)malloc(sizeof(char *) * len)))
		return (NULL);
//	printf("DEBUG 4\n");
	tab[len - 1] = 0;
	len = 0;
	closedir(dirp);
//	printf("DEBUG 5\n");
	dirp = opendir(str);
	while ((dstream = readdir(dirp)) != NULL)
	{
//		printf("DEBUG 6\n");
		if (!(tab[len] = (char *)malloc(sizeof(char) * (ft_strlen(dstream->d_name) + 1))))
			return (NULL);
		tab[len++] = dstream->d_name;
	}
	//tab[len] = 0;
	closedir(dirp);
	option.file = 2;
	//at this point, consider return value for sorting in -l format i.e. info file-by-file
	dir_content = dir_content_list(tab, option, str);
	return (dir_content);
}
