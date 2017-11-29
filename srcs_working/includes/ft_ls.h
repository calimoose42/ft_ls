/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 12:22:58 by arohani           #+#    #+#             */
/*   Updated: 2017/11/07 11:18:18 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <sys/syslimits.h>

# include <dirent.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>
# include <errno.h>
# include "../../libft/includes/libft.h"

typedef struct		s_files
{
	char			name[NAME_MAX];	//provides max bytes for a file name i.e. 255, no need to malloc
	char			*link;
	char			path[PATH_MAX];	//1024 byte limit
	char			full_path[PATH_MAX + NAME_MAX];
	char			perm[12];
	int				error;
	struct stat		buf;
	struct passwd	*own;
	struct group	*group;
	time_t			date;
	char			*raw_date;
	char			cleandate[13];
	char			special_date[12];
	struct s_files 	*next_parent;		//FIND A WAY TO USE THIS TO STOCK AND INCREMENT PARENT DIRECTORY OF EVERY SUB-DIRECTORY
	struct s_files	*next;
	struct s_files	*prev;
	struct s_files	*sub_dir;
	struct dirent 	*dptr;
}					t_files;

typedef struct		s_opt
{
	char			*parent;
	t_files			*R_par;
	int				no_perm;
	int				R_args;
	int				combo;
	long 			block;
	int				l;
	int				r;
	int				rec;
	int				a;
	int				t;
	int				file; //-1 for error list, 1 for file list, 0 for dir list, 2 for dir contents
}					t_opt;

t_opt		scan_options(char *str);
t_files		*dc_list(char *curr_dir, t_opt option);
void		permission_denied(char *str, t_opt option);
void		all_args(char **tab, t_opt option);
t_opt		check_combo(t_files *list, t_opt option);
t_files		*error_list(t_files *args);
t_files		*reverse_lex(t_files *list, t_opt option);
void		print_list(t_files *args);
t_files		*time_sort_list(t_files *list, t_opt option);
void		switch_list_content(t_files *a, t_files *b);
t_files		*regular_args(t_files *args, t_opt option);
t_files		*dir_args(t_files *args, t_opt option);
t_files		*dir_recursive(t_files *sub_dirs, t_opt option);
char		*make_new_path(char *path, char *file);
void		display_errors(t_files *args);
void		display_regular_files(t_files *args, t_opt option);
void		display_directories(t_files *dirs, t_opt option);
void		does_not_exist(char *str);
void		display_directories(t_files *args, t_opt option);
void		long_format(t_files *list, t_opt option);
int			digits(int n);
int			column_size(t_files *list, int link);
t_files		*dir_content_tab(char *str, t_opt option);
t_files		*dir_content_list(char **tab, t_opt option, char *str);
void		display_dir_content(t_files *list, t_opt option);
t_opt		dir_block_size(t_files *list, t_opt option);
void		illegal_option(char option);
void		print_dir_content(t_files *dc, char *curr_dir, t_opt option);
char		*get_full_path(char *path, char *file);
void		recursive_start(t_files *list, t_opt option);

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
