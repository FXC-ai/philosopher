SRCS	=	main.c utils.c routine_philo.c atoi.c args_parser.c philo_creators.c free_philos.c utils_philo.c utils_philo2.c

OBJS	= ${SRCS:.c=.o}

CFLAGS	= -Wall -Werror -Wextra

CC		= gcc

RM		= rm -f

NAME 	= philo

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	${RM}  $(NAME)

re: fclean all

.PHONY: all clean fclean re