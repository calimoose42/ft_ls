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


/*
** 	TRYING TO simply analyze, sort and recursively call each sub-dir content before advancing in list. Print name to verify stream done properly */

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
	t_files			*dirs = NULL;

	if (sub_dirs != NULL)
		sorted = (option.t == 1) ? time_sort_list(sub_dirs, option) : reverse_lex(sub_dirs, option);
	if (sorted == NULL)
		return (NULL);
	while (sorted)
	{
		if (S_ISDIR(sorted->buf.st_mode))
		{

			printf("\nfolder name is: %s\npath name is: \n\n", sorted->name, sorted->path);
			dirs = dir_content_tab(ft_strjoin(sorted->path, sorted->name), option);
		}
		sorted = sorted->next;
	}
	return (NULL);
}

/*t_files		*dir_recursive(t_files *sub_dirs, t_opt option) 	
{
	t_files			*sorted = NULL;		//to store sorted sub_dir list which will be feed to disiplay or option.l
	static t_files	*sub_next = NULL;
	static int 		last = 0;

	option.R_par = (option.R_par == NULL && last == 0) ? sub_dirs : option.R_par;	//initializes option.R_par i.e. PARENT list of sub-directory list
//	if (sub_dirs == NULL && sub_next == NULL && option.R_par->next) for prior effort to read very alst parent subdirectory
//		option.R_par = option.R_par->next;
	if (sub_dirs != NULL)
	{
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
		sorted = (option.t == 1) ? time_sort_list(sub_dirs, option) : reverse_lex(sub_dirs, option);
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
*/