SRCS = 	philosophers.c \
			init_data.c \
			philo_utils.c \
			actions.c \
			time.c \
			print.c \
			death.c \

OBJS = ${SRCS:.c=.o}

PROG = philo

CC = cc

%.o: %.c
	$(CC) -fsanitize=thread -g -Wall -Wextra -Werror -pthread -c $< -o $@

$(PROG): $(OBJS)
			$(CC)  -o ${PROG} $(SRCS)


all	:	${PROG}

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(PROG)

re	:	fclean all

.PHONY	:	all clean
			fclean re