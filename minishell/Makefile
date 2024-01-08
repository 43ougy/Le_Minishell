DIR = ./srcs/
UTILS_DIR = $(DIR)/utils/
PARSE_DIR = $(DIR)/parsing/
EXEC_DIR = $(DIR)/execution/
BUILT_DIR = $(DIR)/builtins/

SRC =	$(DIR)main.c						\
		$(DIR)running.c						\
		$(UTILS_DIR)utils1.c				\
		$(UTILS_DIR)utils2.c				\
		$(UTILS_DIR)utils3.c				\
		$(UTILS_DIR)utils4.c				\
		$(UTILS_DIR)utils5.c				\
		$(UTILS_DIR)utils6.c				\
		$(UTILS_DIR)utils7.c				\
		$(PARSE_DIR)check_parse.c			\
		$(PARSE_DIR)parsing.c				\
		$(PARSE_DIR)parsing_utils.c			\
		$(PARSE_DIR)token.c					\
		$(PARSE_DIR)token_ext.c				\
		$(PARSE_DIR)linked_list.c			\
		$(EXEC_DIR)execution.c				\
		$(EXEC_DIR)execute.c				\
		$(EXEC_DIR)heredoc.c				\
		$(EXEC_DIR)in_red.c					\
		$(EXEC_DIR)out_red.c				\
		$(BUILT_DIR)cd.c					\
		$(BUILT_DIR)echo.c					\
		$(BUILT_DIR)env.c					\
		$(BUILT_DIR)exit.c					\
		$(BUILT_DIR)export.c				\
		$(BUILT_DIR)pwd.c					\
		$(BUILT_DIR)unset.c					\

CC = gcc
RM = rm -f
DEBUG = -g3
INCLUDE = -I ./include/
NAME = minishell
FLAG = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

.c.o	:
	$(CC) $(FLAG) $(DEBUG) $(INCLUDE) -c $< -o $(<:.c=.o)

all : $(NAME)

leaks: $(NAME)
	valgrind --suppressions=./.valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes --read-var-info=yes ./minishell

# echo >>ra >te >rge <wrth <<EOF arg1 >rth"w"$USER"erg"'   g' $?

$(NAME) : $(OBJ)
	$(CC) $(FLAG) -o $(NAME) $(OBJ) -lreadline

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : minishell clean fclean re

.SILENT:
