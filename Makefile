NAME		= Cub3D

SRC_MLX	= ./minilibx
SRC_LIBFT	= ./libft

SRC 		=	cub parse parse_map wall_1 wall_2 sprite_1 sprite_2 \
				move key utils bitmap utils_2 \


FILES = $(addsuffix .c, $(SRC))

LIBFT = $(SRC_LIBFT)/libft.a

OBJ = $(FILES:.c=.o)

CC			= clang 

LIB_FLAGS	= -lmlx -framework OpenGL -framework AppKit

FLAGS		= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(SRC_LIBFT) && make clean -C $(SRC_LIBFT)
	make -C $(SRC_MLX)
	$(CC) -o $(NAME) $(LIBFT) -L $(SRC_MLX) $(LIB_FLAGS) $(OBJ) $(FLAGS) -g

%.o:%.c
	$(CC) $(CFLAGS) -I $(LIBFT) -o $@ -c $<

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

.PHONY:            all clean fclean re
