CC = gcc
WFLAGS = -Wall -Werror -Wextra -g -g3 -ggdb

SRCDIR = srcs
OBJDIR = objs
BONUS_OBJDIR = bonus_objs
INCDIR = .
LIBFT_DIR = lib/libft

NAME = philo 

SRCS = $(shell find $(SRCDIR) -name "*.c")
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

CYAN = \033[36m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(WFLAGS) -MMD -MP -I$(INCDIR) -c $< -g3 -ggdb -o $@

$(NAME): $(OBJS)
	@$(CC) $(WFLAGS) $(OBJS) -o $(NAME)
	@echo "$(CYAN)Build completed: $(NAME)$(RESET)"

clean:
	@rm -rf $(OBJDIR) $(BONUS_OBJDIR)
	@echo "$(CYAN)Project cleaned$(RESET)"

fclean: clean
	@rm -rf $(NAME) checker
	@echo "$(CYAN)Executable removed$(RESET)"

re: fclean all

-include $(DEPS) $(BONUS_DEPS)
