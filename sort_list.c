/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:16:29 by arohani           #+#    #+#             */
/*   Updated: 2017/10/18 18:53:12 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

/* -t sort OVERRIDES -r sort. Non-existant file error messages in ascending order regardless of options */
/* -tr is reverse order of -t sorting */
/* WORKS, including struct stat switch!! */

/*
t_files		*reverse_lex(t_files *list, t_opt option)
{
	char		*tmp_name;
	t_files		*a;
	t_files		*head;
	t_files		*b;
	struct stat	tmp_stat;

	head = list;
	a = list;
	b = a->next;
	print_list(head);
	while (a && b)
	{
		while (b)
		{
			if (option.r == 0)
			{
					printf("\n BEFORE strcmp conditions : a->name = %s, b->name = %s\n", a->name, b->name);
					if (ft_strcmp(a->name, b->name) > 0)
					{
						printf("\n BEFORE SWITCH : a->name = %s, b->name = %s\n", a->name, b->name);
			//			printf("\ntmp->name now = %s\n", tmp->name);
			//			printf("\nlist->name now = %s\n", list->name);
			//			printf("\ncurrent name = %s\n", current->name);
						//list_swap(head, a, b);
						tmp_name = a->name;
						a->name = b->name;
						b->name = tmp_name;
						tmp_stat = a->buf;
						a->buf = b->buf;
						b->buf = tmp_stat;
						printf("\n AFTER SWITCH : a->name = %s, b->name = %s\n", a->name, b->name);
					}
			}
			if (option.r == 1)
			{	
				if (ft_strcmp(a->name, b->name) < 0)
				{
					//list_swap(head, a, b);
						tmp_name = a->name;
						a->name = b->name;
						b->name = tmp_name;
						tmp_stat = a->buf;
						a->buf = b->buf;
						b->buf = tmp_stat;
				}
			}
			printf("\nbefore incrementing b, b->next = %s\n", b->next->name);
			b = b->next;
		}
		a = a->next;
		b = a->next;
	}
	printf("\nHERE'S THE SORTED LIST\n");
	print_list(head);
	return (head);
}*/

t_files			*time_sort_list(t_files *list, t_opt option)
{
	t_files 	*head;
	t_files		*current;
	char		*tmp_name;
	struct stat tmp_stat;
	//char		*date;
	
//	print_list(list);		/*** this is where we print 'time value' for each regular file ***/
	head = list;
	current = head->next;
	while (list && current)
	{
		while (current)
		{
			// if (ft_strcmp("listdir.c", current->name) == 0)
			// 	printf("file name = %s\nmod date = %ld\n", current->name, (current->buf).st_mtimespec.tv_sec);
			// if (ft_strcmp("project_notes", current->name) == 0)
			// 	printf("file name = %s\nmod date = %ld\n", current->name, (current->buf).st_mtimespec.tv_sec);
			// date = ctime(&current->buf.st_mtimespec.tv_sec);
			// printf("file name = %s\nmod date = %s\n", current->name, date);
			//printf("INITIALIZED before starting time sort: time value for %s is %ld\n", current->name, (current->buf).st_mtimespec.tv_sec);
			if (option.r == 0)
			{	
	//			if ((list->buf).st_mtimespec.tv_sec == (current->buf).st_mtimespec.tv_sec)
	//			{
	//				if ((list->buf).st_mtimensec.tv_nsec < (current->buf).st_mtimensec.tv_nsec)
	//			}
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
	//	regular_args(head, option);
	//	dir_args(head);
		//return (head);
	if (option.file == 1 || option.file == 0)
		display_regular_args(head, option);
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
	if (option.file == -1)
		display_errors(head);
	if (option.file == 1 || option.file == 0)
		display_regular_args(head, option);
	return (NULL);
}