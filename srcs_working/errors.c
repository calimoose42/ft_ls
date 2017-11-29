/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:26:50 by arohani           #+#    #+#             */
/*   Updated: 2017/11/29 15:27:01 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>


void			permission_denied(char *str, t_opt option)
{
	int		len;
	printf("the string fed to permission denied is %s\n", str);
	if (ft_strcmp(str, "\"\"") == 0)
		ft_putstr("ft_ls: fts_open: No such file or directory\n");
	else
	{
		ft_putstr("ft_ls: ");
		if (option.rec == 1)
		{
			len = (int)ft_strlen(str);
			while (len >= 0 && str[len] != '/')
				len--;
			ft_putstr(str + len + 1);
		}
		else
			ft_putstr(str);
		ft_putstr(": Permission denied\n");
	}
}

void		does_not_exist(char *str)	/*must be fed arguments that are already sorted*/
{
	ft_putstr("ft_ls: ");
	ft_putstr(str);
	ft_putstr(": No such file or directory\n");
}

void	illegal_option(char option)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(option);
	write (1, "\nusage: ft_ls [-Ralrt] [file ...]\n", 34);
	exit (-1);
}