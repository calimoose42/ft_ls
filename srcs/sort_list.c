/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:16:29 by arohani           #+#    #+#             */
/*   Updated: 2017/11/03 18:03:23 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

/* -t sort OVERRIDES -r sort. Non-existant file error messages in ascending order regardless of options */
/* -tr is reverse order of -t sorting */
/* WORKS, including struct stat switch!! */

t_files			*time_sort_list(t_files *list, t_opt option)
{
	t_files 	*head;
	t_files		*current;
	char		*tmp_name;
	struct stat tmp_stat;
	
	head = list;
	current = head->next;
	while (list && current)
	{
		while (current)
		{
			if (option.r == 0)
			{	
				if (list && current && ((list->buf).st_mtimespec.tv_sec < (current->buf).st_mtimespec.tv_sec))
				{			
					tmp_name = list->name;
					list->name = current->name;
					current->name = tmp_name;
					tmp_stat = list->buf;
					list->buf = current->buf;
					current->buf = tmp_stat;		
				}
			}
			else if (option.r == 1)
			{
				if (list && current && ((list->buf).st_mtimespec.tv_sec > (current->buf).st_mtimespec.tv_sec))
				{					
					tmp_name = list->name;
					list->name = current->name;
					current->name = tmp_name;
					tmp_stat = list->buf;
					list->buf = current->buf;
					current->buf = tmp_stat;					
				}
			}
			current = current->next;
		}
		list = list->next;
		current = list->next;
	}
	(option.file == 1 && option.l != 1) ? display_regular_files(head, option) :
	(option.file == 0 && option.l != 1) ? display_directories(head, option) :
	(option.file == 2) ? display_dir_content(head, option) : long_format(head, option);
	//(option.l == 1) ? long_format(head, option) : return (NULL);
/*	if ((option.file == 1 || option.file == 0) && option.l != 1)
		display_regular_args(head, option);
	else if (option.file == 2)
		display_dir_content(head, option);	
	else if (option.l == 1)
		long_format(head, option);
	return (NULL); */
	return (NULL);
}

t_files			*reverse_lex(t_files *list, t_opt option)
{
	char		*tmp_name;
	t_files		*current;
	t_files		*head;
	struct stat	tmp_stat;

	head = list;
	current = list->next;
	while (list && current)
	{
		while (current)
		{
			if (option.r == 0 || option.r == -1)
			{
				if (ft_strcmp(list->name, current->name) > 0)
				{
					tmp_name = list->name;
					list->name = current->name;
					current->name = tmp_name;
					tmp_stat = list->buf;
					list->buf = current->buf;
					current->buf = tmp_stat;
				}
			}
			else if (option.r == 1)
			{
				if (ft_strcmp(list->name, current->name) < 0)
				{
					tmp_name = list->name;
					list->name = current->name;
					current->name = tmp_name;
					tmp_stat = list->buf;
					list->buf = current->buf;
					current->buf = tmp_stat;
				}
			}
			current = current->next;
		}
		list = list->next;
		current = list->next;
	}
	(option.file == 1 && option.l != 1) ? display_regular_files(head, option) :
	(option.file == 0 && option.l != 1) ? display_directories(head, option) :
	(option.file == 2) ? display_dir_content(head, option) : long_format(head, option);
	/*if (option.file == -1)
		display_errors(head);
	else if ((option.file == 1 || option.file == 0) && option.l != 1)
		display_regular_args(head, option);
	else if (option.file == 2)
		display_dir_content(head, option);
	else if (option.l == 1)
		long_format(head, option);
	return (NULL);*/
	return (NULL);
}