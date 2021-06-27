NAME = minishell
HEAD = ./shell.h
SRCS = ./rtoast/
SRCS_1 = ./truby/
CFLAGS = -Wall -Wextra -Werror
C_FILE =	$(SRCS)begin.c $(SRCS)additionally.c $(SRCS)befor_parser.c $(SRCS)parser.c\
			$(SRCS_1)cd.c $(SRCS_1)echo.c $(SRCS_1)env.c $(SRCS_1)exp.c $(SRCS)dollar.c\
			$(SRCS_1)pwd.c $(SRCS_1)processor.c $(SRCS_1)add_and_delete.c $(SRCS)redirect.c\
			$(SRCS_1)execve.c
O_FILE = $(C_FILE:.c=.o)
all:
	$(MAKE) $(NAME) -j 4
$(NAME): $(O_FILE)
	@make -C ./libft 
	gcc $(O_FILE) ./libft/libft.a -lreadline -o $(NAME)
%.o: %.c $(HEAD)
	gcc -c $(СFLAGS) $< -o $@
clean:
	@make clean -C ./libft
	@rm -f $(O_FILE)
fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re