make -C libft/ fclean && make -C libft/
clang -Wall -Wextra -Werror -I libft/includes -o ft_list_dir.o -c ft_list_dir.c
clang -o ft_list_dir ft_list_dir.o -I libft/includes -L libft/ -lft
rm -f *.o
make -C libft/ fclean
