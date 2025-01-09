CC = cc
CFLAGS = -Wall -Werror -Wextra -g -I include -I libft/include
NAME = minishell
TESTER = minishell_tester
SRC_DIR = src
TEST_DIR = tester
OBJ_DIR = obj

MINISHELL_SRCS =	check_equal.c \
					echo_cmd.c \
					exec_cmd.c \
					file_tmp.c \
					fork.c \
					ft_listnode.c \
					attach.c \
					decomp.c \
					get_path.c \
					detect_var.c \
					export_cmd.c \
					unset_cmd.c \
					fd_take.c \
					pwd_cmd.c \
					env_cmd.c \
					cd_cmd.c \
					realoc.c \
					input.c \
					open_files.c \
					parsing.c \
					prompt.c \
					sanitize_input.c \
					parsing_var.c

MINISHELL_OBJS = $(addprefix $(OBJ_DIR)/, $(MINISHELL_SRCS:.c=.o))

MAIN_SRCS = main.c
MAIN_OBJS = $(addprefix $(OBJ_DIR)/, $(MAIN_SRCS:.c=.o))

TEST_MAIN_SRCS = main_tester.c
TEST_MAIN_OBJS = $(addprefix $(OBJ_DIR)/, $(TEST_MAIN_SRCS:.c=.o))

TEST_SRCS = tester_manager.c \
			tester_block/tester_block.c \
			tester_quote/tester_quote.c \
			tester_checkequal/tester_checkequal.c \
			tester_cmd/tester_cmd.c \
			tester_echo/tester_echo.c

TEST_OBJS = $(addprefix $(OBJ_DIR)/, $(TEST_SRCS:.c=.o))

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(OBJ_DIR) $(LIBFT) $(MINISHELL_OBJS) $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN_OBJS) $(MINISHELL_OBJS) $(LIBFT) -lreadline

$(TESTER): $(OBJ_DIR) $(LIBFT) $(MINISHELL_OBJS) $(TEST_OBJS) $(TEST_MAIN_OBJS)
	$(CC) $(CFLAGS) -o $(TESTER) $(TEST_MAIN_OBJS) $(TEST_OBJS) $(MINISHELL_OBJS) $(LIBFT) -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

test: fclean $(TESTER)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@rm -f $(NAME) $(TESTER)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re test
