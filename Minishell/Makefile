CC = @gcc
RM = @rm -f
FLAG = -Wall -Wextra -Werror -g3
NAME = minishell
SRC = main.c				\
		utils_1.c			\
		utils_2.c			\
		ft_split.c			\
		path_env.c			\
		command.c			\
		handle.c			\
		parser.c			\
		parser_utils.c		\
		pipe_red.c			\
		execution.c			\
		#parser_methods.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@printf "\e[33mCompile...\n\e[0m"
	$(CC) $(FLAG) -o $(NAME) $(OBJ) -lreadline
	@printf "\e[33mCompile\e[0m \e[32mSUCCESS\n\e[0m"

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : minishell
