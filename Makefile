NAME = rtv1
ASSOCIATED_REP = $(NAME).dSYM

LIBFT_REP = libft/
LIBFT = $(LIBFT_REP)libft.a

INCLUDE_FLAG = -I includes/

SRCS_REP = srcs/
HELPER_REP = helpers/
SRCS = $(SRCS_REP)main.c \
		$(SRCS_REP)sphere.c \
		$(SRCS_REP)plane.c \
		$(SRCS_REP)cylinder.c \
		$(SRCS_REP)cone.c \
		$(SRCS_REP)env_init.c \
		$(SRCS_REP)graphic_manager.c \
		$(SRCS_REP)exit.c \
		$(SRCS_REP)camera_init.c \
		$(SRCS_REP)events.c \
		$(SRCS_REP)pixel_drawing.c \
		$(SRCS_REP)scene_init.c \
		$(SRCS_REP)raytracing.c \
		$(SRCS_REP)$(HELPER_REP)constructors.c \
		$(SRCS_REP)$(HELPER_REP)math_tools.c

O_SRCS = $(SRCS:.c=.o)

W_FLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -I ~/Library -g -L ~/Library -lmlx -framework OpenGL -framework \
			AppKit

MATH_FLAG = -lm

%.o: %.c
	@gcc $(W_FLAGS) -c $< -o $@

$(NAME):
	make -C $(LIBFT_REP)
	gcc $(INCLUDE_FLAG) $(MLX_FLAGS) $(MATH_FLAG) $(SRCS) $(LIBFT) -o $(NAME)

all: $(NAME)

clean:
	make clean -C $(LIBFT_REP)
	rm -rf $(O_SRCS)

fclean: clean
	make fclean -C $(LIBFT_REP)
	rm -rf $(NAME) $(ASSOCIATED_REP)

re: fclean all

.PHONY: all clean fclean re
