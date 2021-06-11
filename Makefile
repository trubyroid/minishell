NAME = minishell
HEAD = ./rtoast/shell.h
SRCS = ./rtoast/
GNL = ./libft/
CFLAGS = -Wall -Wextra -Werror
C_FILE =	$(SRCS)begin.c $(SRCS)additionally.c $(SRCS)befor_parser.c $(SRCS)parser.c\
			$(GNL)get_next_line.c $(GNL)get_next_line_utils.c
O_FILE = $(C_FILE:.c=.o)
all:
	$(MAKE) $(NAME) -j 4
$(NAME): $(O_FILE)
	gcc $(O_FILE) -o $(NAME)
%.o: %.c $(HEAD)
	gcc -c $(СFLAGS) $< -o $@
clean:
	@rm -f $(O_FILE)
fclean: clean
	@rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re