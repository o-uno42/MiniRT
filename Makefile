CC = gcc
CFLAGS = -Wall -Wextra -Werror -Llibft -lft -Lminilibx-linux -lml -lXext -lX11 -lm -g
NAME = minirt.a

FILES_SRCS = main.c manage_win.c parsing.c render.c split.c safe_ft.c

FILES_OBJS = $(FILES_SRCS:.c=.o)

HEADER = minirt.h

EXECUTABLE = minirt

MLX_PATH	= minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

all: $(MLX) $(LIBFT) $(NAME) $(EXECUTABLE)

$(LIBFT):
	@make -sC libft/

$(MLX):
	@make -sC minilibix-linux/

$(NAME): $(FILES_OBJS)
		ar rc $(NAME) $(FILES_OBJS)
		ranlib $(NAME)

%.o: %.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(FILES_OBJS)
		$(CC) -o $(EXECUTABLE) $(FILES_OBJS) -Llibft -lft -Lminilibx-linux -lmlx -lXext -lX11 -lm

clean:
		rm -f $(FILES_OBJS)
		make -C $(LIBFT_PATH) clean
		make -C $(MLX_PATH) clean

fclean: clean
		rm -f $(NAME) $(EXECUTABLE)
		make -C $(LIBFT_PATH) fclean

re: fclean all
