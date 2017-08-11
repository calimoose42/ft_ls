make -C libft/ fclean && make -C libft/
clang -Wall -Wextra -Werror -I libft/includes -o ft_inspect_file.o -c ft_inspect_file.c
clang -o ft_inspect_file ft_inspect_file.o -I libft/includes -L libft/ -lft
