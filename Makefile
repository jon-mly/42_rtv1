NAME = rtv1
ASSOCIATED_REP = $(NAME).dSYM

LIBFT_REP = libft/
LIBFT = $(LIBFT_REP)libft.a

INCLUDE_FLAG = -I includes/

SRCS_REP = srcs/
HELPER_REP = helpers/
SRCS = main.c \
		shapes_intersection.c \
		shapes_normal.c \
		env_init.c \
		graphic_manager.c \
		exit.c \
		camera_init.c \
		events.c \
		pixel_drawing.c \
		scene_init.c \
		raytracing.c \
		lighting.c \
		deinit.c \
		$(HELPER_REP)constructors.c \
		$(HELPER_REP)math_tools.c

SRC = $(addprefix $(SRCS_REP), $(SRCS))

O_SRCS = $(SRC:.c=.o)

W_FLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -I ~/Library -g -L ~/Library -lmlx -framework OpenGL -framework \
			AppKit

MATH_FLAG = -lm

$(NAME): $(O_SRCS)
	make -C $(LIBFT_REP)
	gcc -g -fsanitize=address $(INCLUDE_FLAG) $(MLX_FLAGS) $(MATH_FLAG) $(SRC) $(LIBFT) -o $(NAME)

%.o: %.c
	@gcc  $(INCLUDE_FLAG) -c $< -o $@

all: $(NAME)

clean:
	make clean -C $(LIBFT_REP)
	rm -rf $(O_SRCS)

fclean: clean
	make fclean -C $(LIBFT_REP)
	rm -rf $(NAME) $(ASSOCIATED_REP)

re: fclean all

.PHONY: all clean fclean re
