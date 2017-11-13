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
#include <string.h>

/* -t sort OVERRIDES -r sort. Non-existant file error messages in ascending order regardless of options */
/* -tr is reverse order of -t sorting */
/* WORKS, including struct stat switch!! */

void			switch_list_content(t_files *a, t_files *b)
{
	char		*tmp_name;
	struct stat tmp_stat;

	tmp_name = a->name;
	a->name = b->name;
	b->name = tmp_name;
	tmp_stat = a->buf;
	a->buf = b->buf;
	b->buf = tmp_stat;
}

t_files			*time_sort_list(t_files *list, t_opt option)
{
	t_files 	*head;
	t_files		*current;
	
	head = list;
	current = head->next;
	while (list && current)
	{
		while (current)
		{
			if (option.r == 0)
				if (list && current && ((list->buf).st_mtimespec.tv_sec < (current->buf).st_mtimespec.tv_sec))
					switch_list_content(list, current);
			if (option.r == 1)
				if (list && current && ((list->buf).st_mtimespec.tv_sec > (current->buf).st_mtimespec.tv_sec))
					switch_list_content(list, current);
			current = current->next;
		}
		list = list->next;
		current = list->next;
	}
	if (option.rec == 1)
		return (head);
	(option.file == 1 && option.l != 1) ? display_regular_files(head, option) :
	(option.file == 0) ? display_directories(head, option) :
	(option.file == 2) ? display_dir_content(head, option) : long_format(head, option);
	//(option.l == 1) ? long_format(head, option) : return (NULL);
	return (NULL);
}

t_files			*reverse_lex(t_files *list, t_opt option)
{
	t_files		*current;
	t_files		*head;

	head = list;
	current = list->next;
	while (list && current)
	{
		while (current)
		{
			if (option.r == 0 || option.r == -1)		//if no reverse, or to manage non-existant files, regular lexographic
				if (ft_strcmp(list->name, current->name) > 0)
					switch_list_content(list, current);
			if (option.r == 1)
				if (ft_strcmp(list->name, current->name) < 0)
					switch_list_content(list, current);
			current = current->next;
		}
		list = list->next;
		current = list->next;
	}
	if (option.rec == 1)
		return (head);
	(option.file == 1 && option.l != 1) ? display_regular_files(head, option) :
	(option.file == 0) ? display_directories(head, option) :
	(option.file == 2) ? display_dir_content(head, option) : long_format(head, option);
	return (NULL);
}