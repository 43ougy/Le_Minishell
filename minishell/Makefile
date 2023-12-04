DIR = ./srcs/
UTILS_DIR = ./utils/

SRC =	$(DIR)main.c						\
		$(DIR)running.c						\
		$(UTILS_DIR)_itoa.c  				\
		$(UTILS_DIR)_split.c  				\
		$(UTILS_DIR)utils_1.c  				\
		$(UTILS_DIR)utils_2.c  				\
		$(UTILS_DIR)utils_3.c				\
		$(UTILS_DIR)utils_4.c

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
