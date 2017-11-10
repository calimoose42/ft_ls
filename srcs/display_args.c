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

void		display_dir_content(t_files *list, t_opt option)
{
	//printf("DEBUG 1 DISPLAY DIR CONTENT\n");
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
	char	*str;

	if (dirs)
	{
		if (dirs->next == NULL && option.file == 0 && option.combo == 0 && option.rec == 0)
			(option.rec == 1) ? dir_content_tab(ft_strjoin(option.parent, dirs->name), option) : dir_content_tab(dirs->name, option);
		else
		{
			while (dirs)
			{
				if (option.rec == 1)
					ft_putchar('\n');
				//option.parent = ft_strjoin(dirs->name, "/");
				//printf("\noption.parent = %s\n", option.parent);
				str = ft_strjoin(dirs->path, dirs->name);
				(option.rec == 1) ? ft_putstr(str) : ft_putstr(dirs->name);
				ft_putstr(":\n");
				//printf("passing str %s to dir content tab\n", str);
				(option.rec == 1) ? dir_content_tab(str, option) : dir_content_tab(dirs->name, option);
				if (dirs->next && option.rec == 0)
					ft_putchar('\n');
				//free(option.parent);
				dirs = dirs->next;
			}
		}
	}
}

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