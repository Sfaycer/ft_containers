CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic
SANITIZE = -fsanitize=address
NAME = tester
SRCS = main.cpp
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

DEP_DIR := $(OBJ_DIR)/.deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.Td
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS)
POSTCOMPILE = mv -f $(DEP_DIR)/$*.Td $(DEP_DIR)/$*.d && touch $@

LDFLAGS =  
LDLIBS = 

#search for library in ./ path

DEF = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
LYELLOW = \033[0;33m
YELLOW = \033[1;33m
BLUE = \033[1;34m
MAGENTA = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m

all:
		@$(MAKE) $(NAME)

$(NAME): $(SRCS)
		@$(CC) $(LDFLAGS) $(LDLIBS) $(CFLAGS) -o $@ $^
		@echo "$(GREEN)Program '$@' is ready to use.$(DEF)"

debug:
		@$(CC) $(LDFLAGS) $(LDLIBS) -o $(NAME) -gdwarf $(SRCS)
		@echo "$(WHITE)Debugging initiated.$(DEF)"

sanitize:
		@$(CC) $(CFLAGS) -o $(NAME) $(SANITIZE) $(SRCS)
		@echo "$(WHITE)Sanitizer initiated.$(DEF)"

leaks: $(NAME)
		@leaks --atExit -- ./$(NAME);

clean:

cleandebug:
		@rm -rf $(NAME).dSYM
		@echo "$(MAGENTA)Debug files were deleted.$(DEF)"

fclean: clean cleandebug
		@rm -f $(NAME)
		@echo "$(MAGENTA)Program '$(NAME)' was deleted.$(DEF)"

re: fclean all

include $(wildcard $(DEPFILES))

.PHONY: all clean fclean re bonus cleandep debug
