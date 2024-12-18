CC = cc
CFLAGS = -Wall -Werror -Wextra -I include -I libft/include
NAME = minishell

MINISHELL_SRCS =	src/main.c \
					src/parsing.c \
					src/prompt.c \
					src/input.c \
					tester/tester_traitment.c \
					tester/tester_quote/tester_quote.c \
					tester/tester_block/tester_block.c \
					src/sanitize_input.c

OBJS = $(MINISHELL_SRCS:.c=.o)

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re
