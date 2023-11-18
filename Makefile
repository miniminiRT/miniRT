#-------------------------------------------

BLACK       =   "\033[0;30m"
GRAY        =   "\033[1;30m"
RED         =   "\033[1;31m"
GREEN       =   "\033[0;32m"
YELLOW      =   "\033[1;33m"
PURPLE      =   "\033[0;35m"
CYAN        =   "\033[1;36m"
WHITE       =   "\033[1;37m"
EOC         =   "\033[0;0m"
LINE_CLEAR  =   "\x1b[1A\x1b[M"

#-------------------------------------------

SRC			=	main.c \
				utils.c \
				phong_light.c \
				print_scene.c \
				ray.c setting.c \
				shadow.c \
				setting_plane.c \
				setting_cylinder.c \
				setting_sphere.c \
				setting_scene.c \
				./hook/key_hook_move.c \
				./hook/key_hook_rotate.c \
				./hit_object/plane.c \
				./hit_object/sphere.c \
				./hit_object/cylinder.c \
				./hit_object/utils.c \
				./operator/vec_operator1.c \
				./operator/vec_operator2.c \
				./operator/vec_operator3.c
				
OBJ			=	$(SRC:.c=.o)
MLX_DIR 	= minilibx
MLX			= libmlx.a
HEADER		= miniRT.h
OPTION 		= -L./ -lmlx -framework OpenGL -framework AppKit
LIBFT_DIR	= libft
LIBFT 		= libft.a
NAME		= miniRT
CC			= cc
RM 			= rm -rf
CFLAGS		= -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):  $(OBJ) $(HEADER) $(MLX) $(LIBFT)
		cp ./$(MLX_DIR)/$(MLX) $(MLX)
		cp ./$(LIBFT_DIR)/$(LIBFT) $(LIBFT)
		$(CC) $(CFLAGS) -g -fsanitize=address $(OPTION) $(OBJ) $(MLX) $(LIBFT) -o $(NAME) -I$(HEADER)
		@echo $(GREEN)"miniRT made." $(EOC)

%.o: 		%.c
		@$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@
	
$(MLX):
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
		@$(RM) $(OBJ)
		$(RM) $(MLX)
		$(RM) $(LIBFT)
		make clean -C $(MLX_DIR)
		make fclean -C $(LIBFT_DIR)
		@echo $(GREEN)"cleaned." $(EOC)

fclean:		clean
		@$(RM) $(NAME)
		@echo $(GREEN)"fcleaned." $(EOC)

re:			$(MAKE) fclean
			$(MAKE) all
			
.PHONY:		clean fclean re
