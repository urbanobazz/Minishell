NAME    := 	minishell
CC      := 	cc -Wextra -Wall -Werror -g
INCLUDE :=	-I ./include \
			-I ./libft
LIBS    := 	-lreadline \
			-L ./libft -lft
SRCS    :=	src/main.c \
			src/core/lexer.c \
			src/core/parser.c \
			src/core/heredoc.c \
			src/core/expander.c \
			src/core/executor.c \
			src/builtins/switch.c \
			src/builtins/nav.c \
			src/builtins/env.c \
			src/builtins/set.c \
			src/utils/error.c \
			src/utils/free.c \
			src/utils/list.c \
			src/utils/init.c
OBJDIR  := 	obj
OBJS    := 	$(SRCS:%.c=$(OBJDIR)/%.o)

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)/src
	@mkdir -p $(OBJDIR)/src/core
	@mkdir -p $(OBJDIR)/src/builtins
	@mkdir -p $(OBJDIR)/src/utils

$(OBJDIR)/%.o: %.c
	@$(CC) -o $@ -c $< $(INCLUDE) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft && make clean -C ./libft
	@$(CC) $(OBJS) $(INCLUDE) -o $(NAME) $(LIBS)

clean:
	@rm -rf $(OBJDIR)
	@make clean -C ./libft

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
