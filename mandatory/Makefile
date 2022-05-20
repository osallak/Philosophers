NAME = philo
SRCS = srcs/philosophers.c \
	srcs/list_sources.c\
	srcs/parser.c\
	srcs/utils.c \

RM = rm -rf
CC = cc
OBJS = $(SRCS:%.c=%.o)
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $^ -o $@

%.o : %.c philo.h
		$(CC) $(CFLAGS) -c $< -I . -o $@
clean :
		$(RM) $(OBJS) $(B_OBJS)
fclean : clean
		$(RM) $(NAME) $(NAME_B)
