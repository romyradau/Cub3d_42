# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/02 14:12:49 by mjeyavat          #+#    #+#              #
#    Updated: 2022/05/09 13:55:48 by rschleic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3d

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

SRC = main.c window.c parser.c read_tools.c string_tools.c error_messages.c\

OBJ = $(SRC:.c=.o);

LINKED_OBJ = ./NEW_MLX42/*.o ./libft/*.o

all: linked_objects $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SRC) -Llibft -lft NEW_MLX42/libmlx42.a -I include -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME)

objects:
	$(CC) $(CFLAGS) $(OBJ) $(LINKED_OBJ)

linked_objects:
	make -C ./libft
	make -C ./NEW_MLX42

clean:
	rm -f ./libft/*.a ./NEW_MLX42/*.a 

fclean: clean
	rm -f $(NAME) ./libft/*.o ./NEW_MLX42/*/*.o *.o

re: fclean all