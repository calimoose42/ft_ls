/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:23:45 by arohani           #+#    #+#             */
/*   Updated: 2017/11/03 18:08:08 by arohani          ###   ########.fr       */
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
		//if ((args->buf).st_mtimespec.tv_sec)
		//{
			//date = ctime(&args->buf.st_mtimespec.tv_sec);
			//printf("time value for %s is %s\n%ld\n", args->name, date, (args->buf).st_mtimespec.tv_sec);
		//}				
		printf("%s\n", args->name);
		args = args->next;
	}
}

t_files		*dir_args(t_files *args, t_opt option) 	//creates list of directories passed as argument and sends to sorting functions
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
	if (dirs && option.R_args == 1)
		dir_recursive(dirs, option);	//sends dirs passed as argument to recursive as sub_head
	else if (dirs)
	{
		option.file = 0;
		(option.t == 1) ? time_sort_list(dirs, option) : reverse_lex(dirs, option);
	}
	return (NULL);
}

t_files		*regular_args(t_files *args, t_opt option) //creates list of files passed as argument and sends to sorting functions
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
		}
		else
			args = args->next;
	}
	if (regular)
	{
		option.file = 1;
		(option.t == 1) ? time_sort_list(regular, option) : reverse_lex(regular, option);
	}
	return (NULL);
}

t_files			*error_list(t_files *args)
{
	t_files		*errors = NULL;
	t_files		*current = NULL;
	int			first;
	t_opt		tmp = {NULL, NULL, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

	first = 0;
	while (args && first != 1)
	{
		if (args->error == 1)
		{
			if (!(current = (t_files *)malloc(sizeof(t_files))))
				return (NULL);
			errors = current;
			current->name = args->name;
			current->error = 1;
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
			current->error = 1;
			current->name = args->name;
			current->next = NULL;
		}
		args = args->next;
	}
	if (errors)
		reverse_lex(errors, tmp);
	return (NULL);
}

t_opt		check_combo(t_files *list, t_opt option) //checks if both files and directories are passed as arg, which influences display format
{
	int		file = 0;
	int		dir = 0;

	while (list && option.file != 2)
	{
		while (list && list->error == 1)
			list = list->next;
		if (list && (S_ISDIR(list->buf.st_mode)))
			dir++;
		if (list && list->error == 0 && !(S_ISDIR(list->buf.st_mode)))
			file++;
		if (file > 0 && dir > 0)
		{
			option.combo = 1;
			return (option);
		}
		list = list->next;
	}
	if (!(file > 0 && dir > 0))
		option.combo = 0;
	return (option);
}

void		all_args(char **tab, t_opt option)	/*taken directly from av in main, must store and sort, then if_exists, before ANY non-error displaying*/
{
	int 		i;
	t_files		*args = NULL;
	t_files 	*current = NULL;

	i = 0;
	if (!(current = (t_files *)malloc(sizeof(t_files))))
		return ;
	args = current;
	current->name = ft_strdup(tab[i++]);
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
	option = check_combo(args, option);
	error_list(args);
	regular_args(args, option);
	dir_args(args, option);
}