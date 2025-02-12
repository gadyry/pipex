NAME = pipex
NAME_BONUS = pipex_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_MAN = ./mandatory/*.C
OBJ_MAN = $(SRC_MAN:.c=.o)

SRC_BON = ./bonus/ft_split_bonus.c    ./bonus/get_next_line_utils_bonus.c ./bonus/here_doc_bonus.c  ./bonus/utils_bonus.c \
  ./bonus/get_next_line_for_bonus.c  ./bonus/herdoc_pipes_bonus.c  ./bonus/pipex_bonus.c    ./bonus/utils_path_bonus.c
OBJ_BON = $(SRC_BON:.c=.o)



all : $(NAME)

bonus : $(NAME_BONUS)

$(NAME) : $(OBJ_MAN)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_MAN)

$(NAME_BONUS) : $(OBJ_BON)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BON)


mandatory/%.o : mandatory/%.c mandatory/pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o : bonus/%.c bonus/pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@


clean :
	rm -rf $(OBJ_MAN) $(OBJ_BON)

fclean : clean
	rm -rf $(NAME) $(NAME_BONUS)

re : fclean all

.PHONY: fclean