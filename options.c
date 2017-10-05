/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 12:22:34 by arohani           #+#    #+#             */
/*   Updated: 2017/10/05 12:24:05 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

t_opt	scan_options(char *str)
{
	int 	i;
	t_opt	option = {0, 0, 0, 0, 0};

	i = 1;
	while (str[i])
	{
		option.l = (str[i] != 'l' && option.l == 0) ? 0 : 1;
		option.rec = (str[i] != 'R' && option.rec == 0) ? 0 : 1;
		option.t = (str[i] != 't' && option.t == 0) ? 0 : 1;
		option.r = (str[i] != 'r' && option.r == 0) ? 0 : 1;
		option.a = (str[i] != 'a' && option.a == 0) ? 0 : 1;
		i++;
	}
	return (option);
}