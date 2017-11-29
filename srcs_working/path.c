/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 13:58:20 by arohani           #+#    #+#             */
/*   Updated: 2017/11/28 13:58:40 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

char	*make_new_path(char *path, char *file)
{
	char	*new;
	size_t	len;

	len = ft_strlen(path) + ft_strlen(file) + 2; //2 for joining '/' and null-terminator
	new = NULL;
	if (!(new = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	if (file[0] == '/' || file[0] == '~')
		new = ft_strdup(file);		//file is the path if it starts with one of these 2 chars
	else
	{
		new = ft_strcpy(new, path);	//starts filling new path with original path
		new = ft_strcat(new, "/");	//concats '/' to original path
		new = ft_strcat(new, file); //concats file or folder to backslash-ended path
	}
	return (new);
}