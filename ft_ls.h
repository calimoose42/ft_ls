/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 12:22:58 by arohani           #+#    #+#             */
/*   Updated: 2017/08/18 15:41:27 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>
# include "libft/includes/libft.h"
# include <dirent.h>

typedef struct		s_list_ls
{
	struct dirent	*dstream;
	DIR				*dirp;
	struct stat		buf;
	struct passwd	*owner;
	struct group	*group;
	int				i;
	char			*date;
	char			cleandate[13];
	char			special_date[12];
	int				j;
	int				k;
}					t_list_ls;

typedef struct		s_elem	//to store details of each file read within directory stream
{
	char			*name;
//	char			*path;
	time_t			date;
	mode_t			st_mode;
	nlink_t			st_nlink;
	uid_t			st_uid;
	gid_t			st_gid;
	off_t			st_size;
	blkcnt_t		st_blocks;
	dev_t			st_rdev;
	int				isdir;
	struct s_elem	*next;
}					t_elem;

#endif
