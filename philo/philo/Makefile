NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

SRCS = main.c init.c philosophers.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
