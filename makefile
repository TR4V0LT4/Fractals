NAME = fractol

SRC = main.c draw.c fractals.c events.c param.c colors.c

OBJ = ${SRC:%.c=%.o}

FLAGS = -Wall -Wextra -Werror

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_INC = -I $(MLX_DIR)

LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

%.o: %.c
	cc $(FLAGS) $(MLX_INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(MLX_DIR)
	cc $(FLAGS) $(OBJ) $(MLX_LIB) $(LDFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ)
	make -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)

re: fclean all
