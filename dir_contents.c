/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_contents.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 14:09:55 by arohani           #+#    #+#             */
/*   Updated: 2017/11/03 17:45:04 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

t_files		*dir_content_list(char **tab, t_opt option, char *str)
{
	int 		i;
	t_files		*head = NULL;
	t_files 	*current = NULL;
	char		*parent = NULL;

	i = 0;
	parent = ft_strjoin(str, "/");
	while (tab[i] && option.a == 0 && tab[i][0] == '.')
		i++;
	if (!(tab[i]))
		return (NULL);
	if (!(current = (t_files *)malloc(sizeof(t_files))))
		return (NULL);
	head = current;
	current->name = ft_strdup(tab[i++]);
	current->path = ft_strjoin(parent, current->name);
	current->error = (lstat(current->path, &current->buf) < 0) ? 1 : 0;
	while (tab[i])
	{
		while (option.a == 0 && tab[i][0] == '.')
			i++;
		if (!(current->next = (t_files *)malloc(sizeof(t_files))))
			return (NULL);
		current = current->next;
		current->name = ft_strdup(tab[i++]);
		current->path = ft_strjoin(parent, current->name);
		current->error = (lstat(current->path, &current->buf) < 0) ? 1 : 0;
		if (tab[i] == 0)
			current->next = NULL;
	}
	if (head)
		(option.t == 1) ? time_sort_list(head, option) : reverse_lex(head, option);
	return (head);
}

void	dir_content_tab(char *str, t_opt option)
{
	struct dirent 	*dstream;
	DIR 			*dirp = NULL;
	long int		len;
	char			**tab = NULL;

	len = 1;
	dirp = opendir(str);
	if (dirp == NULL)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(str);
		ft_putstr(": Permission denied\n");
		return ;
	}
	while ((dstream = readdir(dirp)) != NULL)
		len++;
	if (!(tab = (char **)malloc(sizeof(char *) * len)))
		return ;
	tab[len - 1] = 0;
	len = 0;
	closedir(dirp);
	dirp = opendir(str);
	while ((dstream = readdir(dirp)) != NULL)
	{
		if (!(tab[len] = (char *)malloc(sizeof(char) * (ft_strlen(dstream->d_name) + 1))))
			return ;
		tab[len++] = dstream->d_name;
	}
	//tab[len] = 0;
	closedir(dirp);
	option.file = 2;
	//at this point, consider return value for sorting in -l format i.e. info file-by-file
	dir_content_list(tab, option, str);
}
