CC = @gcc
RM = @rm -f
FLAG = -Wall -Wextra -Werror
NAME = minishell
SRC = ra_shell.c			\
		SRC/utils_1.c		\
		SRC/utils_2.c		\
		SRC/command.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAG) -o $(NAME) $(OBJ) -lreadline

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : minishell
