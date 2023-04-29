SRCS	=	main.c routine_philo.c routine_manager.c utils.c

OBJS	= ${SRCS:.c=.o}

CFLAGS	= -Wall -Werror -Wextra

CC		= gcc

RM		= rm -f

NAME 	= philosopher

INCLUDE = includes

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -I $(INCLUDE)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	${RM}  $(NAME)

re: fclean all

.PHONY: all clean fclean re