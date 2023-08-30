CC = @gcc
RM = @rm -f
FLAG = -Wall -Wextra -Werror
NAME = minishell
SRC = main.c			\
		utils_1.c		\
		utils_2.c		\
		utils_3.c		\
		utils_4.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAG) -o $(NAME) $(OBJ) -lreadline
	@printf "\e[33mCompile...\n\e[0m"
	@printf "\e[33mCompile\e[0m \e[32mSUCCESS\n\e[0m"

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : minishell
