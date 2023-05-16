SRCS	=	main.c utils.c routine_philo.c routine_manager.c atoi.c args_parser.c

OBJS	= ${SRCS:.c=.o}

CFLAGS	= -Wall -Werror -Wextra

CC		= gcc

RM		= rm -f

NAME 	= philosopher

DEBUG	= debug

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

$(DEBUG): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -fsanitize=thread -g

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	${RM}  $(NAME)

re: fclean all

.PHONY: all clean fclean re