/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:16:29 by arohani           #+#    #+#             */
/*   Updated: 2017/10/16 17:48:02 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

/* -t sort OVERRIDES -r sort. Non-existant file error messages in ascending order regardless of options */
/* -tr is reverse order of -t sorting */
/* WORKS, including struct stat switch!! */

t_files			*get_previous(t_files *head, t_files *a)
{
	t_files		*current;
	t_files		*pre_a;

	if (head == a)
		return (NULL);
	current = head;
	pre_a = NULL;
	while (current && current != a)
	{
		pre_a = current;
		current = current->next;
	}
	if (current != a)
	{
		ft_putstr("ERROR: node not found!\n");
		exit (-1);
	}
	return (pre_a);
}

void			list_swap(t_files *head, t_files *a, t_files *b)
{
	t_files		*pre_a;
	t_files		*pre_b;
	t_files		*a_next;
	t_files		*b_next;
	t_files		*temp;
/* STOCK ALL pre_a, a or pre_a->next, a->next, pre_b, b or pre_b->next, b->next before switching a and b!! */ 
	if (!(head && a && b))
		return ;
	pre_a = get_previous(head, a);
	pre_b = get_previous(head, b);
	a_next = a->next;
	b_next = b->next;
	temp = a;
	printf("BEFORE:\na = %s\na->next = %s\npre_b = %s\nb = %s\nb->next = %s\n", a->name, a->next->name, pre_b->name, b->name, b->next->name);
	pre_a = (pre_a == NULL) ? head : pre_a;
	pre_a->next = b;
	pre_a->next->next = a_next;
	pre_b->next = temp;
	pre_b->next->next = b_next;
	printf("AFTER:\npre_a = %s\na = %s\na->next = %s\npre_b = %s\nb = %s\nb->next = %s\n", pre_a->name, a->name, a->next->name, pre_b->name, b->name, b->next->name);
/*	pre_a = pre_b;
	pre_b = pre_temp;
	temp = a;
	a = b;
	if (!(pre_b)
*/	
/*
	if (head == NULL || a == NULL || b == NULL)
		return ;
	pre_a = get_previous(head, a);
	pre_b = get_previous(head, b);
	printf("\nbefore switch, a = %s, b = %s\n", a->name, b->name);
	if (pre_a)
		b = pre_a->next;
		//pre_a->next = b;	//use head to analyze previous notes, *a in get_previous to find previous to position passed as 2nd param
	if (pre_b)
		a = pre_b->next;
		//pre_b->next = a;
	temp = NULL;
	temp = a->next;
	a->next = b->next;
	b->next = temp;
	if (head == a)
		head = b;
	else
	{
		if (head == b)
			head = a;
	}
*/	
}


t_files			*time_sort_list(t_files *list, t_opt option)
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
						printf("\nmod time of %s is %ld\n", list->name, (list->buf).st_mtimespec.tv_sec);
						printf("\nmod time of %s is %ld\n", current->name, (current->buf).st_mtimespec.tv_sec);
						tmp_name = list->name;
						list->name = current->name;
						current->name = tmp_name;
						tmp_stat = list->buf;
						list->buf = current->buf;
						current->buf = tmp_stat;
						printf("\nmod time of %s is %ld\n", list->name, (list->buf).st_mtimespec.tv_sec);
						printf("\nmod time of %s is %ld\n", current->name, (current->buf).st_mtimespec.tv_sec);
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
	//	regular_args(head, option);
	//	dir_args(head);
		//return (head);
	}
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
			if (option.r == 1)
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
	if (option.file == 1)
		display_regular_args(head, option);
	return (NULL);
}

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