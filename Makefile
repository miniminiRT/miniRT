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

SRC			=	mandatory/main.c \
				mandatory/utils.c \
				mandatory/point_color/phong_light.c \
				mandatory/point_color/shadow.c \
				mandatory/setting_obj/setting.c \
				mandatory/setting_obj/setting_plane.c \
				mandatory/setting_obj/setting_cylinder.c \
				mandatory/setting_obj/setting_sphere.c \
				mandatory/setting_obj/setting_scene.c \
				mandatory/setting_obj/setting_light.c \
				mandatory/check_input/error.c \
				mandatory/check_input/error2.c \
				mandatory/check_input/check_range.c \
				mandatory/check_input/utils2.c \
				mandatory/print_scene/print_scene.c \
				mandatory/print_scene/print_scene_utils.c \
				mandatory/hook/key_hook_move.c \
				mandatory/hook/key_hook_rotate.c \
				mandatory/hit_object/plane.c \
				mandatory/hit_object/sphere.c \
				mandatory/hit_object/cylinder.c \
				mandatory/hit_object/utils.c \
				mandatory/operator/vec_operator1.c \
				mandatory/operator/vec_operator2.c \
				mandatory/operator/vec_operator3.c

BONUS_SRC	= 	bonus/main.c \
				bonus/utils.c \
				bonus/point_color/phong_light.c \
				bonus/point_color/shadow.c \
				bonus/setting_obj/setting.c \
				bonus/setting_obj/setting_plane.c \
				bonus/setting_obj/setting_cylinder.c \
				bonus/setting_obj/setting_sphere.c \
				bonus/setting_obj/setting_scene.c \
				bonus/setting_obj/setting_light.c \
				bonus/check_input/error.c \
				bonus/check_input/error2.c \
				bonus/check_input/check_range.c \
				bonus/check_input/utils2.c \
				bonus/print_scene/print_scene.c \
				bonus/print_scene/print_scene_utils.c \
				bonus/hook/key_hook_move.c \
				bonus/hook/key_hook_rotate.c \
				bonus/hit_object/plane.c \
				bonus/hit_object/sphere.c \
				bonus/hit_object/cylinder.c \
				bonus/hit_object/utils.c \
				bonus/operator/vec_operator1.c \
				bonus/operator/vec_operator2.c \
				bonus/operator/vec_operator3.c


OBJ			=	$(SRC:.c=.o)
B_OBJ		=	$(BONUS_SRC:.c=.o)
MLX_DIR 	= minilibx
MLX			= libmlx.a
HEADER		= mandatory/miniRT.h
B_HEADER	= bonus/miniRT.h
OPTION 		= -L./ -lmlx -framework OpenGL -framework AppKit
LIBFT_DIR	= libft
LIBFT 		= libft.a
NAME		= miniRT
B_NAME		= miniRT
CC			= cc
RM 			= rm -rf
CFLAGS		= -Wall -Wextra -Werror

all:		.MAKE_ALL

bonus:		.MAKE_BONUS


.MAKE_ALL:  $(OBJ) $(HEADER) $(MLX) $(LIBFT)
		cp ./$(MLX_DIR)/$(MLX) $(MLX)
		cp ./$(LIBFT_DIR)/$(LIBFT) $(LIBFT)
		$(CC) $(CFLAGS) $(OPTION) $(OBJ) $(MLX) $(LIBFT) -o $(NAME) -I$(HEADER)
		@echo $(GREEN)"miniRT made." $(EOC)
		$(RM) ./MAKE_BONUS
		touch $@

.MAKE_BONUS: $(B_OBJ) $(B_HEADER) $(MLX) $(LIBFT)
		cp ./$(MLX_DIR)/$(MLX) $(MLX)
		cp ./$(LIBFT_DIR)/$(LIBFT) $(LIBFT)
		$(CC) $(CFLAGS) $(OPTION) $(B_OBJ) $(MLX) $(LIBFT) -o $(B_NAME) -I$(B_HEADER)
		@echo $(GREEN)"miniRT made." $(EOC)
		$(RM) ./MAKE_ALL
		touch $@

%.o: 		%.c
		@$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

$(MLX):
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
		@$(RM) $(OBJ)
		@$(RM) $(B_OBJ)
		$(RM) $(MLX)
		$(RM) $(LIBFT)
		make clean -C $(MLX_DIR)
		make fclean -C $(LIBFT_DIR)
		$(RM) .MAKE_ALL
		$(RM) .MAKE_BONUS
		@echo $(GREEN)"cleaned." $(EOC)

fclean:		clean
		@$(RM) $(NAME)
		@$(RM) $(B_NAME)
		@echo $(GREEN)"fcleaned." $(EOC)

re:			$(MAKE) fclean
			$(MAKE) all

.PHONY:		clean fclean re bonus
