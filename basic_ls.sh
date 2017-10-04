make -C libft/
clang -Wall -Wextra -Werror -I libft/includes basic_ls.c -o basic_ls -L libft/ -lft
rm -f *.o
make -C libft/ fclean
