NAME	:= minishell
CFLAGS	:= -Wextra -Wall -Werror -g
HEADERS	:= -I ./include
SRCS	:=	src/main.c \
			src/lexer.c \
			src/error.c
OBJS	:= ${SRCS:.c=.o}
LIBS	:= -lreadline

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) -o $(NAME) $(LIBS)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re