/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:23:45 by arohani           #+#    #+#             */
/*   Updated: 2017/10/11 18:14:14 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

//void		does_not_exist(char *str)	/*must be fed arguments that are already sorted*/
/*{
	ft_putstr("ft_ls: ");
	ft_putstr(str);
	ft_putstr(": No such file or directory\n");
//	exit (-1);
}
*/
void		print_list(t_files *args)
{
	while (args != NULL)
	{
		printf("%s\n", args->name);
/*		if (args->error == 1)
			//does_not_exist(args->name);
			printf("args->error = %d\n", args->error);
*/		args = args->next;
	}
}

t_files		*reverse_lex(t_files *list, t_opt option)
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
	printf("trying to print sorted list now\n");
	print_list(head);
	return (head);
}

t_files		*error_list(t_files *args, t_opt option)
{
	t_files		*errors;
	t_files		*current;
	int			first;

	first = 0;
	while (args && first != 1)
	{
		if (args->error == 1)
		{
			if (!(current = (t_files *)malloc(sizeof(t_files))))
				return (NULL);
			errors = current;
			current->name = args->name;
			current->next = NULL;
			first = 1;
		}
		args = args->next;
	}
	while (args)
	{
		if (args && args->error == 1)
		{
			if (!(current->next = (t_files *)malloc(sizeof(t_files))))
				return (NULL);
			current = current->next;
			current->name = args->name;
			current->next = NULL;
		}
		args = args->next;
	}
	if (errors)
	{
		printf("sending the following list of error files to sort : \n");
		print_list(errors);
		reverse_lex(errors, option);
		return (errors);
	}
	return (NULL);
}

t_files		*all_args(char **tab, t_opt option)	/*taken directly from av in main, must store and sort, then if_exists, before ANY non-error displaying*/
{
	int 		i;
//	int 		j;
//	struct stat	buf;
	t_files		*args;
	t_files 	*current;

	i = 0;
	if (!(current = (t_files *)malloc(sizeof(t_files))))
		return (NULL);
	args = current;
	current->name = tab[i++];
	if (lstat(current->name, &current->buf) < 0)
		current->error = 1;
	if (!(tab[i]))
		current->next = NULL;
	while (tab[i])
	{
		if (!(current->next = (t_files *)malloc(sizeof(t_files))))
			return (NULL);
		current = current->next;
		current->name = tab[i++];
		if (lstat(current->name, &current->buf) < 0)
			current->error = 1;
		if (tab[i] == 0)
			current->next = NULL;
	}
	//error_list(args, option);
	reverse_lex(args, option);
	return (args);	/* returns all args, NOT sorted, with stocked stat structures and file error verification to manage after sorting */
}
