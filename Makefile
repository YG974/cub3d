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

SRC_GL	= ./minilibx_opengl_20191021/.

SRC 		= main.c /
		
CC			= gcc

LIB_FLAGS	= -lmlx -framework OpenGL -framework AppKit

FLAGS		= -Wall -Wextra -Werror

OBJ        = $(addprefix $(SRC), $(SRC:.c=.o))

$(SRC)%.o:    $(SRC)%.c
	$(CC) $(FLAGS) -o $@ -c -L $(SRC_GL) 

$(NAME):         $(OBJ)
	ar rc $(NAME) $(OBJ)

all:	$(NAME)

clean:
	rm -f $(OBJ)

fclean:         clean
	rm -f $(NAME)

re:             fclean all

test:	${NAME}
	gcc ${NAME} main.c
	./a.out
.PHONY:            all clean fclean re
