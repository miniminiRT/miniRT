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

SRC			=	*.c
OBJ			=	$(SRC:.c=.o)
MLX_DIR 	= minilibx
MLX			= libmlx.a
HEADER		= miniRT.h
OPTION 		= -L./ -lmlx -framework OpenGL -framework AppKit
NAME		= miniRT
CC			= cc
RM 			= rm -rf
CFLAGS		= -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):  $(OBJ) $(HEADER) $(MLX)
		cp ./$(MLX_DIR)/$(MLX) $(MLX)
		$(CC) $(CFLAGS) $(OPTION) $(OBJS) $(MLX) -o $(NAME) -I$(HEADER)
		@echo $(GREEN)"miniRT made." $(EOC)
# @$(CC) $(OBJ) -o $(NAME)

%.o: 		%.c
		@$(CC) $(CFLAGS) -c $< -o $@
	
$(MLX):
	make -C $(MLX_DIR)

clean:
		@$(RM) $(OBJ)
		$(RM) $(MLX)
		make clean -C $(MLX_DIR)
		@echo $(GREEN)"cleaned." $(EOC)

fclean:		clean
		@$(RM) $(NAME)
		@echo $(GREEN)"fcleaned." $(EOC)

re:			$(MAKE) fclean
			$(MAKE) all
			
.PHONY:		clean fclean re
