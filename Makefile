.PHONY:	all clean fclean re

NAME	=	philo

FLAGS	=	-Wall -Wextra -Werror

SRC		=	arguments.c forks.c initialize.c main.c philosopher.c time.c utils.c

OBJ		=	arguments.o forks.o initialize.o main.o philosopher.o time.o utils.o

all:		$(NAME)

$(NAME):	$(SRC) philosophers.h
	gcc $(FLAGS) -c $(SRC)
	gcc $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:		clean
	rm -f $(NAME)

re:			fclean all
