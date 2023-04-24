NAME = philo

SRCS = utils.c sim.c sim_utils.c reaper.c parsing.c main.c init.c behavior.c

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

all:	${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o $@

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re:	fclean all