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

	i = 0;
	option.parent = (option.parent == NULL) ? ft_strjoin(str, "/") : option.parent;
	while (tab[i] && option.a == 0 && tab[i][0] == '.')
		i++;
	if (!(tab[i]))
		return (NULL);
	if (!(current = (t_files *)malloc(sizeof(t_files))))
		return (NULL);
	head = current;
	current->name = ft_strdup(tab[i++]);
	current->path = ft_strjoin(option.parent, current->name);
	current->error = (lstat(current->path, &current->buf) < 0) ? 1 : 0;
	while (tab[i])
	{
		while (option.a == 0 && tab[i][0] == '.')
			i++;
		if (!(current->next = (t_files *)malloc(sizeof(t_files))))
			return (NULL);
		current = current->next;
		current->name = ft_strdup(tab[i++]);
		current->path = ft_strjoin(option.parent, current->name);
		current->error = (lstat(current->path, &current->buf) < 0) ? 1 : 0;
		if (tab[i] == 0)
			current->next = NULL;
	}
	option = dir_block_size(head, option);
	if (head)
		(option.t == 1) ? time_sort_list(head, option) : reverse_lex(head, option);
	if (option.rec == 1)
		dir_args(head, option);
	return (head);
}

t_files		*dir_content_tab(char *str, t_opt option)
{
	struct dirent 	*dstream;
	DIR 			*dirp = NULL;
	long int		len;
	char			**tab = NULL;
	t_files			*dir_content;

	len = 1;
	dirp = opendir(str);
	if (dirp == NULL)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(str);
		ft_putstr(": Permission denied\n");
		return (NULL);
	}
	while ((dstream = readdir(dirp)) != NULL)
		len++;
	if (!(tab = (char **)malloc(sizeof(char *) * len)))
		return (NULL);
	tab[len - 1] = 0;
	len = 0;
	closedir(dirp);
	dirp = opendir(str);
	while ((dstream = readdir(dirp)) != NULL)
	{
		if (!(tab[len] = (char *)malloc(sizeof(char) * (ft_strlen(dstream->d_name) + 1))))
			return (NULL);
		tab[len++] = dstream->d_name;
	}
	//tab[len] = 0;
	closedir(dirp);
	option.file = 2;
	//at this point, consider return value for sorting in -l format i.e. info file-by-file
	dir_content = dir_content_list(tab, option, str);
	return (dir_content);
}
