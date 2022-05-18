NAME = philo
SRCS = srcs/philosophers.c \
		srcs/list_sources.c \
		srcs/parser.c \
		srcs/utils.c \

OBJCS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror

NAME : $(OBJS)
	$(CC) -pthread $^ -o $@
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)
fclean : clean
	rm -f $(NAME)

re : fclean NAME