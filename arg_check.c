/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:23:45 by arohani           #+#    #+#             */
/*   Updated: 2017/11/03 15:03:21 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void		print_list(t_files *args)
{
	//char	*date;
	printf("About to print a list\n");
	while (args != NULL)
	{
		/*if ((args->buf).st_mtimespec.tv_sec)
		{
			date = ctime(&args->buf.st_mtimespec.tv_sec);
			printf("time value for %s is %s\n%ld\n", args->name, date, (args->buf).st_mtimespec.tv_sec);
		}
		*/				
		printf("%s\n", args->name);
		args = args->next;
	}
}

t_files		*dir_args(t_files *args, t_opt option) 	//no need for -a sorting here, but DONT FORGET IT once reaching directory content analysis
{
	t_files		*dirs = NULL;
	t_files		*current = NULL;

	while (args && (args->error == 1 || !(S_ISDIR(args->buf.st_mode))))
		args = args->next;
	if (args)
	{
		if (!(current = (t_files *)malloc(sizeof(t_files))))
			return (NULL);
		dirs = current;
		current->name = args->name;
		current->buf = args->buf;
		args = args->next;
	}
	if (current)
		current->next = NULL;
	while (args)
	{
		if (args->error == 0 && (S_ISDIR(args->buf.st_mode)))
		{
			if (!(current->next = (t_files *)malloc(sizeof(t_files))))
				return (NULL);
			current = current->next;
			current->name = args->name;
			current->buf = args->buf;
			current->next = NULL;
			args = args->next;
		}
		else
			args = args->next;
	}
	if (dirs)
	{
		option.file = 0;
		if (option.t == 1)
			time_sort_list(dirs, option);
		else if (option.t == 0)
			reverse_lex(dirs, option);
	}
	return (NULL);
}

t_files		*regular_args(t_files *args, t_opt option)
{
	t_files		*regular;
	t_files		*current = NULL;
	
	while (args && (current == NULL))
	{
		if (args->error == 0 && !(S_ISDIR(args->buf.st_mode)))
		{
			if (!(current = (t_files *)malloc(sizeof(t_files))))
				return (NULL);
			regular = current;
			current->name = args->name;
			current->buf = args->buf;
			args = args->next;
		}
		else
			args = args->next;
	}
	if (current)
		current->next = NULL;
	while (args)
	{
		if (regular && args->error == 0 && !(S_ISDIR(args->buf.st_mode)))
		{
			if (!(current->next = (t_files *)malloc(sizeof(t_files))))
				return (NULL);
			current = current->next;
			current->name = args->name;
			current->buf = args->buf;
			current->next = NULL;
			args = args->next;
			//current = current->next;
			//printf("INITIALIZED before starting time sort: time value for %s is %ld\n", regular->name, (regular->buf).st_mtimespec.tv_sec);
		}
		else
			args = args->next;
	}
	// printf("2nd element name is %s, time value = %ld\n", regular->next->name, (regular->next->buf).st_mtimespec.tv_sec);
	if (regular)
	{
		option.file = 1;
		if (option.t == 1)
			time_sort_list(regular, option);
		else if (option.t == 0)
			reverse_lex(regular, option);
	}
	return (NULL);
}

t_files			*error_list(t_files *args)
{
	t_files		*errors = NULL;
	t_files		*current = NULL;
	int			first;
	t_opt		tmp = {-1, -1, -1, -1, -1, -1};

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
		reverse_lex(errors, tmp);
	return (NULL);
}

void		all_args(char **tab, t_opt option)	/*taken directly from av in main, must store and sort, then if_exists, before ANY non-error displaying*/
{
	int 		i;
	t_files		*args = NULL;
	t_files 	*current = NULL;

	//printf("DEBUG 1\n");
	i = 0;
	if (!(current = (t_files *)malloc(sizeof(t_files))))
		return ;
	args = current;
	current->name = ft_strdup(tab[i++]);
	current->error = (lstat(current->name, &current->buf) < 0) ? 1 : 0;
	if (!(tab[i]))
		current->next = NULL;
	//printf("DEBUG 2\n");
	while (tab[i])
	{
		if (!(current->next = (t_files *)malloc(sizeof(t_files))))
			return ;
		//printf("DEBUG 3\n");
		current = current->next;
		current->name = ft_strdup(tab[i++]);
		current->error = (lstat(current->name, &current->buf) < 0) ? 1 : 0;
		if (tab[i] == 0)
			current->next = NULL;
		//printf("DEBUG 4\n");
	}
	//print_list(args);	/*** this is where CORRECT date values are saved ***/
	//printf("DEBUG 5\n");
	error_list(args);
	//printf("\n finished error list management \n");
	regular_args(args, option);
	//printf("\n finished regular file list management \n");
	dir_args(args, option);
	//printf("\n finished error list, reg list and dir list display, work on dir content next\n");
}