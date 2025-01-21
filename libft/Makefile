AR			= ar rcs
CC			= cc
CFLAGS		= -Wall -Werror -Wextra

INLCUDES	= includes/
SRC_DIR		= srcs/
OBJ_DIR		= objs/

CFLAGS		+= -I../$(INLCUDES)

SRC			= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c	\
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c			\
			ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c		\
			ft_strrchr.c ft_strcmp.c ft_strncmp.c ft_memchr.c ft_memcmp.c		\
			ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c			\
			ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c			\
			ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c		\
			ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c			\
			ft_lstlast.c ft_lstadd_back.c ft_lstfree_content.c ft_lstdelone.c	\
			ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_printf.c ft_printf_utils.c\
			ft_fprintf.c ft_fprintf_utils.c get_next_line.c

OBJ			= $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))

NAME		= libft.a


all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
