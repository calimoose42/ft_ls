/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 17:58:24 by arohani           #+#    #+#             */
/*   Updated: 2017/10/19 17:22:02 by arohani          ###   ########.fr       */
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
void		display_regular_args(t_files *args, t_opt option)	//after all necessary sorting
{
	if (option.l == 1)
		long_format(args, option);
	if (option.file == 0)
		write(1, "\n", 1);
	while (args)
	{
		ft_putstr(args->name);
		if (option.file == 0)
		{
			ft_putstr(":\n");
		//	display_dir_contents();
		}
		else
			write(1, "\n", 1);
		args = args->next;
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