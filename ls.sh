make -C libft/ fclean && make -C libft/
clang -Wall -Wextra -Werror -I libft/includes -c listdir.c optionmain.c
clang -Wall -Wextra -Werror -I libft/includes -c optionmain.c
clang -Wall -Wextra -Werror optionmain.o listdir.o libft/libft.a -o ft_ls
rm -f *.o
make -C libft/ fclean
