
NAME = philo
CC = cc
CFLAGS	= -Wall -Wextra -Werror
SRC = main.c\
		str_utils.c\
		utils.c\
		init.c\
		routine.c

OBJS = $(SRC:.c=.o)
DEPS = $(OBJS:.o=.d)

%.o: %.c Makefile
	$(CC) $(CFLAGS)	-c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re