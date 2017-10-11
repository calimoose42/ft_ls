make -C libft/
clang -Wall -Wextra -Werror -c options.c arg_check.c main_ls.c
clang -Wall -Wextra -Werror options.o arg_check.o main_ls.o libft/libft.a -o ft_ls
rm -f *.o
make -C libft/ fclean