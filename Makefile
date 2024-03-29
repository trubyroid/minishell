NAME = minishell
HEAD = ./shell.h
SRCS = ./rtoast/
SRCS_1 = ./truby/
CFLAGS = -Wall -Wextra -Werror
C_FILE =	$(SRCS)begin.c $(SRCS)additionally.c $(SRCS)before_parser.c $(SRCS)parser.c\
			$(SRCS_1)cd.c $(SRCS_1)echo.c $(SRCS_1)env.c $(SRCS_1)export.c $(SRCS)dollar.c\
			$(SRCS_1)pwd.c $(SRCS_1)processor.c $(SRCS_1)add_env.c $(SRCS)redirect.c\
			$(SRCS_1)execve.c $(SRCS)main.c $(SRCS_1)delete_env.c $(SRCS_1)extra_functions.c\
			$(SRCS_1)closing.c $(SRCS_1)preprocessor.c $(SRCS_1)extra_functions2.c $(SRCS)utils.c\
			$(SRCS)utils_for_remove.c $(SRCS)signal.c $(SRCS)utils2.c $(SRCS)before_parser_utils.c\
			$(SRCS)error.c $(SRCS)dollar_utils.c $(SRCS)parser_utils.c $(SRCS_1)errors.c\
			$(SRCS)command_parser_utils.c $(SRCS_1)extra_functions3.c $(SRCS)redirect_utils.c
O_FILE = $(C_FILE:.c=.o)
RL = -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/ -I/Users/$(USER)/.brew/Cellar/readline/8.1/include -lreadline
# RL = -L/usr/local/Cellar/readline/8.1/lib/ -I/usr/local/Cellar/readline/8.1/include -lreadline
all:
	$(MAKE) $(NAME) -j 4
$(NAME): $(O_FILE)
	@make -C ./libft 
	gcc -g $(O_FILE) ./libft/libft.a $(RL) -o $(NAME)
%.o: %.c $(HEAD)
	gcc -c -g $(СFLAGS) $< -o $@
clean:
	@make clean -C ./libft
	@rm -f $(O_FILE)
fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
