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

SRC_MLX	= -I ./minilibx-linux
SRC_LIBFT	= ./libft

SRC 		=	cub parse parse_map wall_1 wall_2 sprite_1 sprite_2 \
				move utils bitmap utils_2 \


FILES = $(addsuffix .c, $(SRC))

LIBFT = $(SRC_LIBFT)/libft.a

OBJ = $(FILES:.c=.o)

CC			= clang

LIB_FLAGS	= -L ./minilibx-linux -lmlx -lXext -lX11 -lm -lbsd

FLAGS		= -O3 -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(SRC_LIBFT) && make clean -C $(SRC_LIBFT)
	make -C $(SRC_MLX)
	$(CC) $(FLAGS) -o $(NAME) $(LIBFT) $(SRC_MLX) $(LIB_FLAGS) $(FLAGS) $(OBJ)


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)
	./$(NAME) "map.cub"

save: $(NAME)
	./$(NAME) "map.cub" "--save"

leaks: $(NAME)
	./Cub3D map.cub &>/dev/null & disown && sleep 1 && leaks Cub3D

.PHONY:            all clean fclean re test save leaks
