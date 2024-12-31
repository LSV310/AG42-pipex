CC			= cc
CFLAGS		= -g3 #-Wall -Werror -Wextra

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

INCLUDES	= includes/
SRC_DIR		= srcs/
OBJ_DIR		= objs/

CFLAGS		+= -I$(INCLUDES)

SRC			= main.c
OBJ			= $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))

NAME		= pipex

all: $(NAME)

# bonus: $(BONUS_NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

# $(BONUS_NAME): $(LIBFT) $(BONUS_OBJ)
# 	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) -o $(BONUS_NAME)

$(LIBFT):
	make -sC $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@make clean -sC $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
#	rm -rf $(NAME) $(BONUS_NAME)
	make fclean -sC libft

re: fclean all

.PHONY: all bonus clean fclean re
