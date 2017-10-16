/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 12:22:58 by arohani           #+#    #+#             */
/*   Updated: 2017/10/16 17:01:49 by arohani          ###   ########.fr       */
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
	long int		date;
	char			*raw_date;
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
	int				file; //-1 for error list, 1 for file list, 0 for dir list
}					t_opt;

typedef struct		s_files
{
	char			*name;
	char			*path;
	int				error;
	struct stat		buf;
	struct passwd	*own;
	struct group	*group;
	time_t			date;
	char			*raw_date;
	char			cleandate[13];
	char			special_date[12];
	struct s_files	*next;
}					t_files;

t_opt	scan_options(char *str);
/* int 	dir_total(char **tab, int file_check);
char	**dir_tab(char	**tab);
char	**sort_dir_tab(char **dir, int r);
t_dirs	*stock_dlist(char **dir, int t, int r);
char	**files_tab(char **tab);
char	**sort_files_tab(char **files, int r);
t_files	*stock_flist(char **files);
char	**stock_dir_content(char *str);
void	stock_from_dlist(t_dirs *dlist, int r, int a);
char	**sort_dir_content(char **dir_data, int r, int a);
t_dirs	*time_sort_dlist(t_dirs	*head, int r);
*/
void		all_args(char **tab, t_opt option);
t_files		*error_list(t_files *args);
t_files		*reverse_lex(t_files *list, t_opt option);
void		print_list(t_files *args);
t_files		*time_sort_list(t_files *list, t_opt option);
t_files		*regular_args(t_files *args, t_opt option);
t_files		*dir_args(t_files *args);
void		display_errors(t_files *args);
void		display_regular_args(t_files *args, t_opt option);
void		does_not_exist(char *str);
void		list_swap(t_files *head, t_files *a, t_files *b);
t_files		*get_previous(t_files *head, t_files *a);

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