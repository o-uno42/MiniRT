CC = gcc
CFLAGS = -Wall -Wextra -Werror -Llibft -lft -Lminilibx-linux -lml -lXext -lX11 -lm -g

NAME = minirt.a
HEADER = includes/minirt.h

SRC_DIR = srcs
OBJ_DIR = objs
GEO_DIR = $(SRC_DIR)/objects
GEOMETRY = $(wildcard $(GEO_DIR)/*.c)
FILES_SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/manage_win.c \
			 $(SRC_DIR)/parsing.c $(SRC_DIR)/split.c $(SRC_DIR)/safe_ft.c \
			 $(SRC_DIR)/color_creation.c $(SRC_DIR)/color.c \
			 $(SRC_DIR)/vector_utils.c $(SRC_DIR)/math_utils.c \
			 $(SRC_DIR)/render.c $(SRC_DIR)/render_inits.c $(SRC_DIR)/rays.c \
			 $(SRC_DIR)/debug_utils.c $(SRC_DIR)/free_functions.c \
			 $(SRC_DIR)/light.c  $(SRC_DIR)/bonus_checker.c \
			 $(GEOMETRY)

FILES_OBJS = $(FILES_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


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
	@make -sC minilibx-linux/

$(NAME): $(FILES_OBJS)
		ar rc $(NAME) $(FILES_OBJS)
		ranlib $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(GEOMETRY) $(HEADER)
		# @mkdir -p $(OBJ_DIR)
		# @mkdir -p $(GEO_DIR)
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(FILES_OBJS)
		$(CC) -o $(EXECUTABLE) $(FILES_OBJS) -Llibft -lft -Lminilibx-linux -lmlx -lXext -lX11 -lm

clean:
		rm -f $(FILES_OBJS)
		make -C $(LIBFT_PATH) clean
		make -C $(MLX_PATH) clean

fclean: clean
		rm -f $(NAME) $(EXECUTABLE)
		rm -rf $(OBJ_DIR)
		make -C $(LIBFT_PATH) fclean

re: fclean all
