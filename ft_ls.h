/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 12:22:58 by arohani           #+#    #+#             */
/*   Updated: 2017/10/05 16:37:11 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <dirent.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>
# include "libft/includes/libft.h"

/*typedef struct		s_list_ls
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
*/

typedef struct		s_dir_data
{
	struct dirent	*dstream;
	DIR				*dirp;
	char			**content;
	char			*name;
	char			*path;
	struct stat		buf;
	struct passwd	*own;
	struct group	*group;
	char			*date;
	char			cleandate[13];
	char			special_date[12];
}					t_dir_data;

typedef struct		s_opt
{
	int				l;
	int				r;
	int				rec;
	int				a;
	int				t;
}					t_opt;

typedef struct		s_files
{
	char			*name;
	char			*path;
	struct stat		buf;
	struct passwd	*own;
	struct group	*group;
	char			*date;
	char			cleandate[13];
	char			special_date[12];
	struct s_files	*next;
}					t_files;

typedef struct		s_dirs
{
	char			*name;
	char			*path;
	struct stat		buf;
	struct passwd	*own;
	struct group	*group;
	char			*date;
	char			cleandate[13];
	char			special_date[12];
	struct s_dirs	*next;
}					t_dirs;

t_opt	scan_options(char *str);
int 	dir_total(char **tab, int file_check);
char	**dir_tab(char	**tab);
char	**sort_dir_tab(char **dir, int r);
t_dirs	*stock_dlist(char **dir, int no_args);
char	**files_tab(char **tab);
char	**sort_files_tab(char **files, int r);
t_files	*stock_flist(char **files);
char	**stock_dir_content(char *str);
void	stock_from_dlist(t_dirs *dlist);

/*
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
*/
#endif