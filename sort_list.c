/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:16:29 by arohani           #+#    #+#             */
/*   Updated: 2017/10/12 16:24:05 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

/* -t sort OVERRIDES -r sort. Non-existant file error messages in ascending order regardless of options */
/* -tr is reverse order of -t sorting */

t_files		*reverse_lex(t_files *list, t_opt option) /* WORKS, including struct stat switch!! */
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
			if (option.r == 0)
				if (ft_strcmp(list->name, current->name) > 0)
				{
					tmp_name = list->name;
					list->name = current->name;
					current->name = tmp_name;
					tmp_stat = list->buf;
					list->buf = current->buf;
					current->buf = tmp_stat;
				}
			if (option.r == 1)
				if (ft_strcmp(list->name, current->name) < 0)
				{
					tmp_name = list->name;
					list->name = current->name;
					current->name = tmp_name;
					tmp_stat = list->buf;
					list->buf = current->buf;
					current->buf = tmp_stat;
				}
			current = current->next;
		}
		list = list->next;
		current = list->next;
	}
	return (head);
}

t_files		*time_sort_list(t_files *list, t_opt option)	/* 	WORKS, including struct stat switch!! */
{
	t_files 	*head;
	t_files		*current;
	char		*tmp_name;
	struct stat tmp_stat;

	if (list && option.t == 1)
	{
		head = list;
		current = list->next;
		while (list && current)
		{
			while (current)
			{
				if (option.r == 0)
				{
					if ((list->buf).st_mtimespec.tv_sec < (current->buf).st_mtimespec.tv_sec)
					{
						tmp_name = list->name;
						list->name = current->name;
						current->name = tmp_name;
						tmp_stat = list->buf;
						list->buf = current->buf;
						current->buf = tmp_stat;
					}
				}
				if (option.r == 1)
				{
					if ((list->buf).st_mtimespec.tv_sec > (current->buf).st_mtimespec.tv_sec)
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
		printf("here is the time-sorted result : \n");
		print_list(head);
		return (head);
	}
	reverse_lex(list, option);
	return (NULL);
}