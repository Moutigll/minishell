CC = cc
CFLAGS = -g -I include -I libft/include -Wall -Wextra -Werror
NAME = minishell
TESTER = minishell_tester
SRC_DIR = src
TEST_DIR = tester
OBJ_DIR = obj

# Recherche de tous les fichiers .c dans src/ sauf main.c
MINISHELL_SRCS = $(filter-out $(SRC_DIR)/main.c, $(shell find $(SRC_DIR) -type f -name "*.c"))
MINISHELL_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(MINISHELL_SRCS))

MAIN_SRCS = src/main.c
MAIN_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(MAIN_SRCS))

TEST_MAIN_SRCS = tester/main_tester.c
TEST_MAIN_OBJS = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_MAIN_SRCS))

TEST_SRCS = $(shell find $(TEST_DIR) -type f -name "*.c")
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_SRCS))

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
