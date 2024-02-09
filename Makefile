NAME    := 	minishell
CC      := 	cc -Wextra -Wall -Werror -g
INCLUDE :=	-I ./include \
			-I ./libft
LIBS    := 	-lreadline \
			-L ./libft -lft
SRCS    := 	src/main.c \
		   	src/lexer.c \
		   	src/error.c
OBJS    := 	$(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) -o $@ -c $< $(INCLUDE) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft
	@$(CC) $(OBJS) $(INCLUDE) -o $(NAME) $(LIBS)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all clean fclean re
