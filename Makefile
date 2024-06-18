NAME		=	server client
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address
LDFLAGS		=	-fsanitize=address
SRCS		=	server.c client.c
LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a
OBJS		=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
    $(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBFT)

$(LIBFT):
    $(MAKE) -C $(LIBFT_DIR)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJS)
    $(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
    rm -f $(NAME)
    $(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re