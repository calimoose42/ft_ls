make -C libft/
clang -Wall -Wextra -Werror -I libft/includes ft_ls.h -c options.c arg_files.c no_args.c main_ls.c arg_directories.c
clang -Wall -Wextra -Werror options.o arg_files.o no_args.o  main_ls.o arg_directories.o libft/libft.a -o new_ls
rm -f *.o
make -C libft/ fclean
