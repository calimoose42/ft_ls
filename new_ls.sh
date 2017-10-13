make -C libft/
clang -Wall -Wextra -Werror -c options.c arg_check.c sort_list.c display_args.c main_ls.c
clang -Wall -Wextra -Werror options.o arg_check.o sort_list.o display_args.o main_ls.o libft/libft.a -o ft_ls
rm -f *.o
make -C libft/ fclean