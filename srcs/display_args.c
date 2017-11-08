/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 17:58:24 by arohani           #+#    #+#             */
/*   Updated: 2017/11/03 17:05:47 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void		does_not_exist(char *str)	/*must be fed arguments that are already sorted*/
{
	ft_putstr("ft_ls: ");
	ft_putstr(str);
	ft_putstr(": No such file or directory\n");
}
/*
void		display_directories(t_files *args, t_opt option)
{
	while (args)
	{
		ft_putstr(args->name);
		write(1, "\n", 1);
		args = args->next;
	}
}
*/

void		display_dir_content(t_files *list, t_opt option)
{
	if (option.l == 1)
		long_format(list, option);
	while (list && option.l == 0)
	{
		ft_putstr(list->name);
		write(1, "\n", 1);
		list = list->next;
	}
}

void		display_regular_files(t_files *args, t_opt option)
{
	while (args)
	{
		ft_putstr(args->name);
		ft_putchar('\n');
		args = args->next;
	}
	if (option.combo == 1)
		ft_putchar('\n');
}

void		display_directories(t_files *dirs, t_opt option)	//after all necessary sorting
{
	if (dirs->next == NULL && option.file == 0 && option.combo == 0)
		dir_content_tab(dirs->name, option);
	else
	{
		while (dirs)
		{
			option.parent = ft_strjoin(dirs->name, "/");
			ft_putstr(dirs->name);
			ft_putstr(":\n");
			dir_content_tab(dirs->name, option);
			if (dirs->next)
				ft_putchar('\n');
			dirs = dirs->next;
		}
	}
}

	/*if (option.file == 1)
		file_check++;
	if (args->next == NULL && option.file == 0)
		single_dir_check++;
	if (option.l == 1)
		long_format(args, option);
	if (option.file == 0 && file_check != 0)
		write(1, "\n\n", 2);
	while (args)
	{
		if (option.file != 0)
			ft_putstr(args->name);
		else if (option.file == 0)
		{
			option.parent = ft_strjoin(args->name, "/");
			if (single_dir_check == 0)
			{
				ft_putstr(args->name);
				ft_putstr(":\n");
			}
			dir_content_tab(args->name, option);
		}
		if (args->next)
			write(1, "\n", 1);
		args = args->next;
	}
	if (option.file != 1)
		file_check = 0;
}
*/
void		display_errors(t_files *args)
{
	if (args)
	{
		while (args)
		{
			does_not_exist(args->name);
			args = args->next;
		}
	}
}