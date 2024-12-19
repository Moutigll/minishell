CC = cc
CFLAGS = -Wall -Werror -Wextra -I include -I libft/include
NAME = minishell
TESTER = minishell_tester
SRC_DIR = src
TEST_DIR = tester

PUSH_SWAP_SRCS =	check_equal.c \
					echo_cmd.c \
					file_tmp.c \
					ft_listnode.c \
					input.c \
					parsing.c \
					prompt.c \
					sanitize_input.c \

MINISHELL_OBJS = $(addprefix $(SRC_DIR)/, $(PUSH_SWAP_SRCS:.c=.o))

NORMAL_SRCS = main.c
NORMAL_OBJS = $(addprefix $(SRC_DIR)/, $(NORMAL_SRCS:.c=.o))

TEST_SRCS = main.c \
			tester_manager.c \
			tester_block/tester_block.c \
			tester_quote/tester_quote.c \
			tester_checkequal/tester_checkequal.c
TEST_OBJS = $(addprefix $(TEST_DIR)/, $(TEST_SRCS:.c=.o))

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(MINISHELL_OBJS) $(NORMAL_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(NORMAL_OBJS) $(MINISHELL_OBJS) $(LIBFT) -lreadline

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: fclean $(LIBFT) $(MINISHELL_OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TESTER) $(TEST_OBJS) $(MINISHELL_OBJS) $(LIBFT) -lreadline
	@make clean

clean:
	@rm -f $(MINISHELL_OBJS) $(NORMAL_OBJS) $(BONUS_OBJS) $(TEST_OBJS)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@rm -f $(NAME) $(CHECKER) $(TESTER)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re test
