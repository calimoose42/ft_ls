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

t_files		*dir_recursive(t_files *sub_dirs, t_opt option) 	
{
	/* NEED SOMETHING LIKE : 
	** if (sub_dirs->next == NULL && (sub_next))
	** { 
			sub_dirs->next_parent = sub_next; i.e. to stock "no_perm, TESTdir" in sub_dirs and recall once sub_dirs completely analyzed
			sub_next = sub_next->next;
			...........
		}
	*/
	t_files			*sorted = NULL;		//to store sorted sub_dir list which will be feed to disiplay or option.l
	static t_files	*sub_next = NULL;
	static int 		last = 0;

	if (sub_dirs)
	{
		printf("\nat top of recursive, sub_dirs = \n");
		print_list(sub_dirs);
		sub_dirs->next_parent = (sub_next) ? sub_next : NULL;
	}
	if (sub_next)
	{
		printf("\nat top of recursive, sub_next = \n");
		print_list(sub_next);
	}
	if (option.R_par)
	{
		printf("\nat top of recursive, option.R_par = \n");
		print_list(option.R_par);
	}
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
		printf("\nat end of recursive, RIGHT BEFORE DISPLAY, sorted directories being displayed before sorted = sorted->next is \n");
		print_list(sorted);
		if (sorted->next_parent != NULL)
		{
			printf("\nat end of recursive, RIGHT BEFORE DISPLAY, next_parent = \n");
			print_list(sorted->next_parent);
			display_directories(sorted, option);
		}
		sorted = sorted->next;
	}
	return (NULL);
}