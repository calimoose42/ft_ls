/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:23:45 by arohani           #+#    #+#             */
/*   Updated: 2017/10/12 17:49:19 by arohani          ###   ########.fr       */
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

t_files		*time_sort_list(t_files *list, t_opt option)
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
		return (head);
	}
	return (NULL);
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
	return (head);
}

t_files		*dir_args(t_files *args, t_opt option) 	//no need for -a sorting here, but DONT FORGET IT once reaching directory content analysis
{
	t_files		*dirs;
	t_files		*current;

	while (args && (args->error == 1 || !(S_ISDIR(args->buf.st_mode))))
		args = args->next;
	if (args)
	{
		if (!(current = (t_files *)malloc(sizeof(t_files *))))
			return (NULL);
		dirs = current;
		current->name = args->name;
		current->buf = args->buf;
		args = args->next;
	}
	while (args && args->next)
	{
		while (args->error == 1 || !(S_ISDIR(args->buf.st_mode)))
		{
			args = args->next;
			if (args == NULL)
			{
				current->next = NULL;
				return (dirs);
			}
		}
		while (args->error == 0 && (S_ISDIR(args->buf.st_mode)))
		{
			if (!(current->next = (t_files *)malloc(sizeof(t_files *))))
				return (NULL);
			current = current->next;
			current->name = args->name;
			current->buf = args->buf;
			args = args->next;
			if (args == NULL)
			{
				current->next = NULL;
				return (dirs);
			}
		}
	}
	reverse_lex(args, option);
	return (NULL);
}

t_files		*regular_args(t_files *args, t_opt option)
{
	t_files		*regular;
	t_files		*current;

	while (args && (args->error == 1 || S_ISDIR(args->buf.st_mode)))
		args = args->next;
	if (args)
	{
		if (!(current = (t_files *)malloc(sizeof(t_files *))))
			return (NULL);
		regular = current;
		current->name = args->name;
		current->buf = args->buf;
		args = args->next;
	}
	while (args && args->next)
	{
		while (args->error == 1 || S_ISDIR(args->buf.st_mode))
		{
			args = args->next;
			if (args == NULL)
			{
				current->next = NULL;
				return (regular);
			}
		}
		while (args->error != 1 && !(S_ISDIR(args->buf.st_mode)))
		{
			if (!(current->next = (t_files *)malloc(sizeof(t_files *))))
				return (NULL);
			current = current->next;
			current->name = args->name;
			current->buf = args->buf;
			//args = (args->next != NULL) ? args->next : args;
			args = args->next;
			if (args == NULL)
			{
				current->next = NULL;
				return (regular);
			}
		}
		if (args->next == NULL)
		{
			current->next = NULL;
			return (regular);
		}
	}
	reverse_lex(args, option);
	return (NULL);
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
		return (errors);
	reverse_lex(args, option);
	return (NULL);
}

t_files		*all_args(char **tab, t_opt option)	/*taken directly from av in main, must store and sort, then if_exists, before ANY non-error displaying*/
{
	int 		i;
	t_files		*args;
	t_files 	*current;

	i = 0;
	if (!(current = (t_files *)malloc(sizeof(t_files))))
		return (NULL);
	args = current;
	current->name = ft_strdup(tab[i++]);
	if (lstat(current->name, &current->buf) < 0)
	current->error = (lstat(current->name, &current->buf) < 0) ? 1 : 0;
	if (!(tab[i]))
		current->next = NULL;
	while (tab[i])
	{
		if (!(current->next = (t_files *)malloc(sizeof(t_files))))
			return (NULL);
		current = current->next;
		current->name = ft_strdup(tab[i++]);
		current->error = (lstat(current->name, &current->buf) < 0) ? 1 : 0;
		if (tab[i] == 0)
			current->next = NULL;
	}
	printf("\n ERROR LIST \n");
	print_list(error_list(args, option));
	printf("\n REGULAR FILES \n");
	print_list(regular_args(args, option));
	printf("\n DIRECTORIES \n");
	print_list(dir_args(args, option));
	if (option.t != 1)
		reverse_lex(args, option);
	if (option.t == 1)
		time_sort_list(args, option);
	return (args);	/* returns all args, NOT sorted, with stocked stat structures and file error verification to manage after sorting */
}