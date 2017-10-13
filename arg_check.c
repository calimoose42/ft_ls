/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:23:45 by arohani           #+#    #+#             */
/*   Updated: 2017/10/13 20:06:00 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void		print_list(t_files *args)
{
	printf("About to print a list\n");
	while (args != NULL)
	{
		printf("%s\n", args->name);
/*		if (args->error == 1)
			//does_not_exist(args->name);
			printf("args->error = %d\n", args->error);
*/		args = args->next;
	}
}

t_files		*dir_args(t_files *args) 	//no need for -a sorting here, but DONT FORGET IT once reaching directory content analysis
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
		current->next = NULL;
		args = args->next;
	}
	while (args)
	{
		if (args && (args->error == 1 || S_ISDIR(args->buf.st_mode)))
			args = args->next;
	/*		if (args == NULL)
			{
				current->next = NULL;
				return (regular);
			}
		}
	*/	while (args && (args->error != 1 && !(S_ISDIR(args->buf.st_mode))))
		{
			if (!(current->next = (t_files *)malloc(sizeof(t_files *))))
				return (NULL);
			current = current->next;
			current->name = args->name;
			current->buf = args->buf;
			//current->next = NULL;
			//args = (args->next != NULL) ? args->next : args;
			args = args->next;
		}
	}
	if (regular)
	{
		print_list(regular);
		printf("\noption.t is %d\n", option.t);
		if (option.t == 1)
			time_sort_list(regular, option);
		if (option.t == 0)
			reverse_lex(regular, option);
	}
	//return (regular);
	return (NULL);
}

t_files			*error_list(t_files *args)
{
	t_files		*errors;
	t_files		*current;
	int			first;
	t_opt		tmp = {-1, -1, -1, -1, -1};

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
		reverse_lex(errors, tmp);
	}
	return (NULL);
}

void		all_args(char **tab, t_opt option)	/*taken directly from av in main, must store and sort, then if_exists, before ANY non-error displaying*/
{
	int 		i;
	t_files		*args;
	t_files 	*current;
	t_opt		tmp = {0, 0, 0, 0, 0};

	option = tmp;
	i = 0;
	if (!(current = (t_files *)malloc(sizeof(t_files))))
		return ;
	args = current;
	current->name = ft_strdup(tab[i++]);
	if (lstat(current->name, &current->buf) < 0)
	current->error = (lstat(current->name, &current->buf) < 0) ? 1 : 0;
	if (!(tab[i]))
		current->next = NULL;
	while (tab[i])
	{
		if (!(current->next = (t_files *)malloc(sizeof(t_files))))
			return ;
		current = current->next;
		current->name = ft_strdup(tab[i++]);
		current->error = (lstat(current->name, &current->buf) < 0) ? 1 : 0;
		if (tab[i] == 0)
			current->next = NULL;
	}
	error_list(args);
	regular_args(args, option);
}