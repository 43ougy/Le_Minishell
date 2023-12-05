DIR = ./srcs/
UTILS_DIR = ./srcs/utils/

SRC =	$(DIR)main.c						\
		$(DIR)running.c						\
		$(UTILS_DIR)_itoa.c  				\
		$(UTILS_DIR)_split.c  				\
		$(UTILS_DIR)alloc_utils.c 			\
		$(UTILS_DIR)check_char_utils.c 		\
		$(UTILS_DIR)check_char_utils_2.c	\
		$(UTILS_DIR)string_utils.c 			\
		$(UTILS_DIR)string_utils_2.c 		\
		$(UTILS_DIR)utils.c

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
	
$(NAME) : $(OBJ)
	$(CC) $(FLAG) -o $(NAME) $(OBJ) -lreadline

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : minishell

.SILENT:
