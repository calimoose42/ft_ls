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

t_files		*dir_recursive(t_files *sub_dirs, t_opt option) 	
{
	t_files			*sorted = NULL;		//to store sorted sub_dir list which will be feed to disiplay or option.l
	static t_files	*sub_next = NULL;
	static int 		last = 0;

	option.R_par = (option.R_par == NULL && last == 0) ? sub_dirs : option.R_par;	//initializes option.R_par i.e. PARENT list of sub-directory list
//	if (sub_dirs == NULL && sub_next == NULL && option.R_par->next) for prior effort to read very alst parent subdirectory
//		option.R_par = option.R_par->next;
	if (sub_dirs != NULL)
	{
		/* if sub_directory list exists, then sort it */
		sorted = (option.t == 1) ? time_sort_list(sub_dirs, option) : reverse_lex(sub_dirs, option);
	}
	else if (sub_dirs == NULL && sub_next != NULL)
	{
		sorted = (option.t == 1) ? time_sort_list(sub_next, option) : reverse_lex(sub_next, option);
		sub_next = NULL;
		if (option.R_par->next)	//to advance root sub_dir once first sub_dir is completely analyzed
			option.R_par = option.R_par->next;
		else if (option.R_par && option.R_par->next == NULL)
		{
			sorted = (option.t == 1) ? time_sort_list(option.R_par, option) : reverse_lex(option.R_par, option);
			option.R_par = option.R_par->next;
		}
	}
	else if (option.R_par != NULL && sub_dirs == NULL && sorted == NULL)
	{	
		/* if sub_directory list DOESN'T exist, but parent_directory DOES (i.e. parent_directory had no permissions or didn't contain any sub-directories) */
		if (option.R_par->next)
			option.R_par = option.R_par->next;	//advance to next parent-directory item (i.e. from libft to srcs)
		else	//i.e. very last root sub-directory found, must recursively analyze... (originally had exit here)
		{
			sub_dirs = option.R_par;
			option.R_par = NULL;
			last = 1;	//notifies function that this is last root sub-directory and option.R_par must be left null
			dir_recursive(sub_dirs, option);
		}
		sub_dirs = option.R_par;
	/*	if (sub_dirs == NULL)
		{
			//printf("MASTER DEBUG\n");
			exit(0);
		}	
	*/	sorted = (option.t == 1) ? time_sort_list(sub_dirs, option) : reverse_lex(sub_dirs, option);
	}
	else if (option.R_par == NULL && sub_dirs == NULL && sorted == NULL)
		exit(0);	//exits once all sub-directories have been analyzed and displayed
	while (sorted)
	{
		if (sorted->next)	//to stock next sub_dir item in case current sub_dir has no permissions or is empty/only hidden files
			sub_next = sorted->next;
		else
			sub_next = NULL;	//resets sub_next once no sub_directories remain in the current leaf
		display_directories(sorted, option);
		sorted = sorted->next;
	}
	return (NULL);
}

t_files		*dir_content_list(char **tab, t_opt option, char *str)
{
	int 		i;
	t_files		*head = NULL;
	t_files 	*current = NULL;
	t_files		*sub_dir = NULL;
	t_files		*sub_head = NULL;

/* DIR CONTENT LIST receives table with all folder contents, option, and folder name, creates list out of it */
	i = 0;		
	option.parent = ft_strjoin(str, "/");
	while (tab[i] && option.a == 0 && tab[i][0] == '.')
	{
		i++;	//handles -a
	}
	if (!(tab[i])) 
	{
		/*if table doesnt exist i.e. only includes hidden files if -a not activated, or is a directory with no file-permissions  */
		if (option.rec == 1)
		{
			/*display the directory content, then feed to dir_recursive to see if there is another folder to advance to*/
			/* THIS may be spot to best handle no_permissions issue, as either no_perm or hidden-files-only folder would be fed to recursive here */
			display_dir_content(head, option);
			dir_recursive(sub_head, option);
		}
	}
	if (!(current = (t_files *)malloc(sizeof(t_files))))
		return (NULL);
	/* reach this part of function if all hidden files are ignored and there are still additional contents within the parent folder */
	head = current;
	current->name = ft_strdup(tab[i++]);
	current->path = ft_strdup(option.parent);
	current->error = (lstat(ft_strjoin(current->path, current->name), &current->buf) < 0) ? 1 : 0;	//STORES stat struct for each file, using full path of file to properly get recognized by lstat
	current->next = NULL;
	if (S_ISDIR(current->buf.st_mode))
	{	
		/* enter here to initialize sub_directory list if first non-hidden item is a directory */
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
		while (option.a == 0 && tab[i][0] == '.')
			i++;
		if (!(current->next = (t_files *)malloc(sizeof(t_files))))
			return (NULL);
		current = current->next;
		current->name = ft_strdup(tab[i++]);
		current->path = ft_strdup(option.parent);
		current->error = (lstat(ft_strjoin(current->path, current->name), &current->buf) < 0) ? 1 : 0;
		if (S_ISDIR(current->buf.st_mode))		//creating list of all sub-directories
		{
			if (!(sub_head))		//first sub-directory created, if not encountered in first non-hidden item
			{
				if (!(sub_dir = (t_files *)malloc(sizeof(t_files))))
					return (NULL);
				sub_dir->name = ft_strdup(current->name);
				sub_dir->buf = current->buf;
				sub_dir->path = ft_strdup(current->path);
				//sub_dir->next = NULL;
				sub_head = sub_dir;
			}
			else		//if sub_directory list already stocked with 1 item, enter here for all additional items 
			{
				if (!(sub_dir->next = (t_files *)malloc(sizeof(t_files))))
					return (NULL);
				sub_dir = sub_dir->next;
				sub_dir->name = ft_strdup(current->name);
				sub_dir->buf = current->buf;
				sub_dir->path = ft_strdup(current->path);
				//sub_dir->next = NULL;
			}
		}
		if (tab[i] == 0) // null-terminates sub-directory list and directory content list once end of dir content table is encountered
		{
			if (sub_dir != NULL)
				sub_dir->next = NULL;
			current->next = NULL;
		}
	}
	option = dir_block_size(head, option); //for use in option.l
	option = check_combo(head, option); //to handle display formatting when arguments are passed, i.e. different format for 1dir argument, vs multiple-dir arg, vs 1dir and 1+ files
	if (option.rec == 1)
	{
		/* feeds to recursive ONLY IF the parent directory contents were properly stored and displayed. Below line displays SORTED dir content before recursive recall */
		(option.t == 1) ? display_dir_content(time_sort_list(head, option), option) : display_dir_content(reverse_lex(head, option), option);
		dir_recursive(sub_head, option);	//then feeds all sub_directories (null if no sub-directories) to recursive function
	}
	if (head)
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
/* PROGRAM starts here with '.' passed as string */
	len = 1;
	dirp = opendir(str);
	if (dirp == NULL)	/*tests for no permissions directory, RETURNS null to main if first directory has no permissions, else to display_directories,
	 which is initialized via recursive */
	{
		ft_putstr("ft_ls: ");
		if (option.rec == 1)
		{
			len = (long int)ft_strlen(str);
			while (len >= 0 && str[len] != '/')
				len--;
			ft_putstr(str + len + 1);
		}
		else
			ft_putstr(str);
		//(option.rec == 1) ? ft_putstr(str + ft_strlen(option.parent)) : ft_putstr(str);
		ft_putstr(": Permission denied\n");
		return (NULL);
	}
	while ((dstream = readdir(dirp)) != NULL) //if dir opened, count all files for mallocing table that will store it
		len++;
	if (!(tab = (char **)malloc(sizeof(char *) * len))) //use first count for memory allocation
		return (NULL);
	tab[len - 1] = 0;		
	len = 0;
	if (dirp != NULL)
		closedir(dirp);
	dirp = opendir(str);		//open again, this time to store file names into table
	while ((dstream = readdir(dirp)) != NULL)
	{
		if (!(tab[len] = (char *)malloc(sizeof(char) * (ft_strlen(dstream->d_name) + 1))))
			return (NULL);
		tab[len++] = ft_strdup(dstream->d_name); //without strdup causes issues i.e. with /dev
	}
	closedir(dirp);
	option.file = 2;
	dir_content = dir_content_list(tab, option, str);	//dir_content_list initialized, after processing will be stored in dir_content, which will RETURN to display_directories
	return (dir_content);
}
