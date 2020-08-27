# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/11 17:31:19 by ygeslin           #+#    #+#              #
#    Updated: 2020/03/11 18:50:40 by ygeslin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= Cub3D

SRC_MLX	= ./minilibx
SRC_LIBFT	= ./libft

SRC 		=	cub parse parse_map wall_1 wall_2 sprite_1 sprite_2 \
				move utils print check_parsing \


FILES = $(addsuffix .c, $(SRC))

LIBFT = $(SRC_LIBFT)/libft.a

OBJ = $(FILES:.c=.o)

CC			= clang 

LIB_FLAGS	= -lmlx -framework OpenGL -framework AppKit

FLAGS		= -Wall -Wextra -Werror -ggdb

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(SRC_LIBFT) && make clean -C $(SRC_LIBFT)
	#make -C $(SRC_MLX)
	$(CC) -o $(NAME) -ggdb $(LIBFT) -ggdb -L $(SRC_MLX) -ggdb $(LIB_FLAGS) -ggdb $(OBJ) -ggdb 


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

test: $(NAME)
	./$(NAME) "map.cub"

.PHONY:            all clean fclean re
