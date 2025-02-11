# 🖥️ FLags
CC = cc
CFLAGS = -g -I include -I libft/include -Wall -Wextra -Werror -MMD -MP
LDFLAGS = -lreadline

# 🏗️ Names
NAME = minishell

# 📂 Folders
SRC_DIR = src
OBJ_DIR = obj
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

# 🔍 Recover files
MINISHELL_SRCS = $(filter-out $(SRC_DIR)/main.c, $(shell find $(SRC_DIR) -type f -name "*.c"))
MINISHELL_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(MINISHELL_SRCS))

MAIN_SRCS = $(SRC_DIR)/main.c
MAIN_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(MAIN_SRCS))

DEPS = $(MINISHELL_OBJS:.o=.d) $(MAIN_OBJS:.o=.d) $(TEST_OBJS:.o=.d)

# 🎨 ANSI colors
GREEN  = \033[1;32m
YELLOW = \033[1;33m
BLUE   = \033[1;34m
RED    = \033[1;31m
RESET  = \033[0m
BOLD   = \033[1m

# 🏗️ Compilation
all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@printf "$(BLUE)🔧 Compiling Libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(OBJ_DIR) $(LIBFT) $(MINISHELL_OBJS) $(MAIN_OBJS)
	@printf "$(YELLOW)🚀 Creating $(BOLD)$(NAME)$(RESET)$(YELLOW)...$(RESET)\n"
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN_OBJS) $(MINISHELL_OBJS) $(LIBFT) $(LDFLAGS)
	@printf "$(GREEN)✅ Compilation success !$(RESET)\n"

# 🛠️ Progression
TOTAL_FILES := $(words $(MINISHELL_SRCS) $(MAIN_SRCS))
COMPILED_FILES := 0

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(eval COMPILED_FILES := $(shell expr $(COMPILED_FILES) + 1))
	@printf "$(BLUE)📦 Compilation [$$(($(COMPILED_FILES) * 100 / $(TOTAL_FILES)))%%] -> $(BOLD)$<$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	$(eval COMPILED_FILES := $(shell expr $(COMPILED_FILES) + 1))
	@printf "$(BLUE)📦 Compilation [$$(($(COMPILED_FILES) * 100 / $(TOTAL_FILES)))%%] -> $(BOLD)$<$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(RED)🧹 Deleting object files...$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_PATH)

fclean: clean
	@printf "$(RED)🗑️ Removing binaries...$(RESET)\n"
	@rm -f $(NAME) $(TESTER)
	@$(MAKE) fclean -C $(LIBFT_PATH)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
