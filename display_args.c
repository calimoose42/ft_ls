/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 17:58:24 by arohani           #+#    #+#             */
/*   Updated: 2017/10/16 17:42:19 by arohani          ###   ########.fr       */
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

void		display_regular_args(t_files *args, t_opt option)	//after all necessary sorting
{
	//t_files		*reg = NULL;

	/*if (args)
	{
		if (option.t == 1)
			reg = time_sort_list(reg, option);
		if (option.t == 0)
			reg = reverse_lex(reg, option);
	}
	*/
	if (option.file == 0)
		return ;
	while (args)
	{
		ft_putstr(args->name);
		write(1, "\n", 1);
		args = args->next;
	}
	if (dir_args(args))
		write (1, "\n", 1);
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