/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 17:29:04 by arohani           #+#    #+#             */
/*   Updated: 2017/11/06 17:29:17 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void		print_dir_content(t_files *dc, char *curr_dir, t_opt option)
{
	static int start = 0;

	if (start > 0 && option.t == 0)	//only display directory name after first content is displayed
	{
		ft_putstr("\n");
		ft_putstr(curr_dir);
		ft_putstr(":\n");
	}
	while (dc)
	{
		while (dc && dc->name[0] == '.' && option.a == 0) //for some reason these lines make us stop recursive one time sooner....
			dc = dc->next;
		if (dc)
		{
			ft_putendl(dc->name);
			dc = dc->next;
		}
	}
	start++;
}

/*char		*get_full_path(char *path, char *file)
{
	char	*full_path;

	if (!(full_path = (char *)malloc(sizeof(ft_strlen(path) + ft_strlen(file) + 1))))
		return (NULL);
	ft_strcpy(full_path, path);
	ft_strcat(full_path, file);
	return (full_path);
}
*/
void		fill_dir_content_list(t_files *list, char *curr_dir, char *file)
{
	char	new_path[PATH_MAX];

	ft_strcpy(list->name, file);
	ft_strcpy(list->path, curr_dir);
	ft_strcat(list->path, "/");
	ft_strcpy(new_path, list->path);
	ft_strcat(new_path, file);
	list->error = (lstat(new_path, &list->buf) < 0) ? 1 : 0;
//	printf("list->error = %d\nnew_path used for lstat is %s\n", list->error, new_path);
	list->next = NULL;
}

t_files		*dc_list(char *curr_dir, t_opt option)
{
	struct dirent 	*dstream;
	DIR 			*dirp = NULL;
	t_files			*dir_content = NULL;
	t_files 		*head = NULL;
	t_files			*tmp = NULL;
	printf("\n\t\tENTERING DC LIST with curr_dir = %s\n", curr_dir);
/* PROGRAM starts here with '.' passed as string */
	dirp = opendir(curr_dir);
	if (dirp == NULL)	/*tests for no permissions directory, RETURNS null to main if first directory has no permissions, else to display_directories, which is initialized via recursive */
	{
		permission_denied(curr_dir, option);
		return (NULL);
	}
	if (!(dir_content = (t_files *)malloc(sizeof(t_files))))
		return (NULL);
	head = dir_content;
	tmp = head;
	if ((dstream = readdir(dirp)) != NULL)
		fill_dir_content_list(dir_content, curr_dir, dstream->d_name);	//to store first item and avoid issue with stocking 1 too many elements in list
	while ((dstream = readdir(dirp)) != NULL)
	{
		if (!(dir_content->next = (t_files *)malloc(sizeof(t_files))))
			return (NULL);
		dir_content = dir_content->next;
		fill_dir_content_list(dir_content, curr_dir, dstream->d_name);
	}
	closedir(dirp);
	tmp = (option.t == 1) ? time_sort_list(head, option) : reverse_lex(head, option);	//here all directory contents are sorted
	print_dir_content(tmp, curr_dir, option);
	if (option.rec == 1)
		recursive_start(tmp, option);
	return (tmp);
}

void			recursive_start(t_files *list, t_opt option)
{
	t_files		*tmp = NULL;
	
	//printf("\nENTERING recursive start\n");
	tmp = list;
	//printf("\nDEBUG 1\n");
	while (tmp)
	{
	//printf("\nDEBUG 2\n");		
		while (tmp && !(S_ISDIR((tmp->buf).st_mode)))
		{
		//	printf("\nDEBUG 3\n");
			tmp = tmp->next;
		//	printf("\nDEBUG 4\n");
		}
		if (tmp && (S_ISDIR((tmp->buf).st_mode)))
		{
		//	printf("\nDEBUG 5\n");			
			if (((tmp->name)[0] == '.' && ft_strcmp(tmp->name, ".") != 0 && ft_strcmp(tmp->name, "..") != 0) || (tmp->name)[0] != '.')
			{
				ft_strcpy(tmp->full_path, tmp->path);
				ft_strcat(tmp->full_path, tmp->name);
				dc_list(tmp->full_path, option);
			}
			tmp = tmp->next;
		}
	} 
}

/*
void					ft_is_directory(t_files *tmp, char *curr_dir, t_flags f)
{
	char				*new_path;

	if (S_ISDIR((tmp)->st_mode))
		if (((tmp)->name[0] == '.' && ft_strcmp((tmp)->name, ".") != 0
		&& ft_strcmp((tmp)->name, "..") != 0) || (tmp)->name[0] != '.')
		{
			new_path = make_path_fl(curr_dir, (tmp)->name);
			if (!f.a)
			{
				if (tmp->name[0] != '.')
				{
					ft_putchar('\n');
					ft_putendl(new_path);
					(tmp)->sub_dir = ft_list(new_path, f);
				}
			}
			else
			{
				ft_putchar('\n');
				ft_putendl(new_path);
				(tmp)->sub_dir = ft_list(new_path, f);
			}
			free(new_path);
		}
}
*/