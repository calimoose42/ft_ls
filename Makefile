# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arohani <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 14:09:54 by arohani           #+#    #+#              #
#    Updated: 2017/11/07 11:55:15 by arohani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CFLAGS = -g -Wall -Wextra -Werror

SRC_DIR = srcs/

SRC = arg_check.c \
	  dir_contents.c \
	  display_args.c \
	  long_format.c \
	  main_ls.c \
	  options.c \
	  sort_list.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	make -C libft/
	gcc $(CFLAGS) -I srcs/includes -c $(addprefix $(SRC_DIR),$(SRC))
	gcc $(CFLAGS) -o $(NAME) $(OBJ) -I libft/includes libft/libft.a
	@echo "\n\t$(NAME) executable created\n"

clean :
	make -C libft clean
	rm -f $(OBJ)
	@echo "\n\t.o files deleted\n"

fclean : clean
	rm -f $(NAME)
	make -C libft fclean
	@echo "\n\t$(NAME) executable deleted\n"

re: fclean all

.PHONY: all clean fclean re
