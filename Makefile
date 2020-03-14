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

SRC_MMS	= ./minilibx_mms_20200219/.

SRC_GL	= ./minilibx_opengl_20191021

SRC 		= cub.c 
		
CC			= gcc

LIB_FLAGS	= -lmlx -framework OpenGL -framework AppKit

FLAGS		= -Wall -Wextra -Werror

OBJ        = $(SRC:.c=.o)

all:		$(NAME)
$(NAME):	$(OBJ)
	$(CC) -o $(NAME) -L $(SRC_GL) $(LIB_FLAGS) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:         clean
	rm -f $(NAME)

re:             fclean all

test:	${NAME}

.PHONY:            all clean fclean re
