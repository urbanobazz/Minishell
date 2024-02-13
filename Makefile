NAME    := 	minishell
CC      := 	cc -Wextra -Wall -Werror -g
INCLUDE :=	-I ./include \
			-I ./libft
LIBS    := 	-lreadline \
			-L ./libft -lft
SRCS    :=	src/main.c \
			src/lexer.c \
			src/error.c \
			src/parser.c \
			src/executor.c \
			src/list_utils.c \
			src/expander.c \
			src/heredoc.c \
			src/free_data.c
OBJDIR  := 	obj
OBJS    := 	$(SRCS:%.c=$(OBJDIR)/%.o)

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)/src

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
