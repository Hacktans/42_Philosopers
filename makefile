SRC = main.c parse.c utils.c actions.c utils2.c
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean : 
		rm -rf $(OBJS)

fclean : 
		rm -rf $(OBJS) $(NAME)

re : fclean $(NAME)

.PHONY: all clean fclean re