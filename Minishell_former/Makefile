CC = @gcc
RM = @rm -f
FLAG = -Wall -Wextra -Werror
NAME = minishell
SRC = main.c					\
		utils_1.c				\
		utils_2.c				\
		utils_3.c				\
		utils_4.c				\
		parser_utils.c			\
		get_line_utils.c		\
		give_properties_utils.c	\
		check_value_utils.c		\
		check_value_utils_2.c	\
		execution_utils.c		\
		execution_utils_2.c		\
		get_cmd_utils.c			\
		get_cmd_utils_2.c		\
		nb_args_utils.c			\
		nb_args_utils_2.c		\
		nb_args_utils_3.c		\
		ft_split.c				\
		get_line.c				\
		command.c				\
		path_env.c				\
		ft_itoa.c				\
		handle.c				\
		parser.c				\
		execution.c				\
		unset_split.c			\
		nb_args_split.c			\
		export_split.c			\
		get_cmd_split.c			\
		set_equals_split.c		\
		running_split.c			\
		execution_split.c		\
		check_value_split.c		\
		give_properties_split.c	\

OBJ = $(SRC:.c=.o)

.c.o	:
	$(CC) $(FLAG) -g3 -I . -c $< -o $(<:.c=.o)

all : $(NAME)
	
$(NAME) : $(OBJ)
	$(CC) $(FLAG) -o $(NAME) $(OBJ) -lreadline

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : minishell
