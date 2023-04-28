#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define EAT 1
#define SLEEP 2
#define THINK 3


typedef struct s_philo 
{

	pthread_t		tid;
	int				id;
	int				state;
	time_t			start_time;

	pthread_mutex_t	*chopstick0;
	pthread_mutex_t	*chopstick1;

	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	time_t			last_eat;

} t_philo;

void	ft_print_tab_philo (t_philo **tab_philo)
{
	int	i;

	i = 0;
	while (tab_philo[i] != NULL)
	{
		printf("        id = [%d]\n", tab_philo[i]->id);
		printf("start_time = [%ld]\n", tab_philo[i]->start_time);
		printf("fork_right = [%p]\n", tab_philo[i]->chopstick0);
		printf("fork_left  = [%p]\n", tab_philo[i]->chopstick1);
		printf("\n");
		i++;
	}

}

time_t	calculate_current_time_ms (time_t start_time_ms)
{
	struct timeval current_time;
	time_t	current_time_ms;
	time_t	result;

	gettimeofday(&current_time, NULL);

	current_time_ms = (current_time.tv_sec * 1000000) + (current_time.tv_usec);
	result = current_time_ms - start_time_ms;
	return (result);
}

void	take_right_fork(t_philo *philo)
{
	printf("\033[1;3%dm%ld ms : Philosopher %d try to take the right fork [%p].\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id, philo->chopstick0);
	pthread_mutex_lock(philo->chopstick0);
	printf("\033[1;3%dm%ld ms : Philosopher %d has taken the right fork [%p].\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id, philo->chopstick0);
}

void	take_left_fork(t_philo *philo)
{
	printf("\033[1;3%dm%ld ms : Philosopher %d try to take the left fork [%p].\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id, philo->chopstick1);
	pthread_mutex_lock(philo->chopstick1);
	printf("\033[1;3%dm%ld ms : Philosopher %d has taken take the left fork [%p].\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id, philo->chopstick1);
}

void	eat(t_philo *philo)
{
	printf("\033[1;3%dm%ld ms : Philosopher %d start to eat.\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id);
	usleep(philo->time_to_eat);
	philo->last_eat = calculate_current_time_ms(philo->start_time);
	printf("\033[1;3%dm%ld ms : Philosopher %d finish to eat.\n\033[0m", (philo->id % 7), philo->last_eat, philo->id);

}

void	leave_right_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->chopstick0);
	printf("\033[1;3%dm%ld ms : Philosopher %d leave the right fork.\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id);

}

void	leave_left_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->chopstick1);
	printf("\033[1;3%dm%ld ms : Philosopher %d leave the left fork.\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id);
}

void	have_a_nape(t_philo *philo)
{
	printf("%ld ms : Philosopher %d is sleeping.\n", calculate_current_time_ms(philo->start_time),philo->id);
	usleep(philo->time_to_sleep);
}

void *routine_philosopher(void *philo)
{
	t_philo			*cpy_ptr_philo;
	struct timeval	current_time;
	time_t			current_time_ms;

	int test;
	
	cpy_ptr_philo = (t_philo *) philo;


	while (1)
	{
		take_right_fork(cpy_ptr_philo);
		take_left_fork(cpy_ptr_philo);
		eat(cpy_ptr_philo);
		leave_right_fork(cpy_ptr_philo);	
		leave_left_fork(cpy_ptr_philo);	
		have_a_nape(cpy_ptr_philo);

		printf("%ld ms : Philosopher %d is thinking.\n", calculate_current_time_ms(cpy_ptr_philo->start_time),(*cpy_ptr_philo).id);

		printf("%ld ms : Philosopher %d is dead.\n", calculate_current_time_ms(cpy_ptr_philo->start_time),(*cpy_ptr_philo).id);
	}
	return NULL;
}


int main ()
{
	int	number_of_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int	number_of_eat;
	int	i;


	t_philo	**tab_philo;
	t_philo	*current_philo;

	struct timeval StartTime;
	time_t	start_time;

	number_of_philo = 2;
	time_to_sleep = 1;
	time_to_eat = 200;

	/* QUELLE HEURE EST-IL ? */
	gettimeofday(&StartTime, NULL);
	start_time = (StartTime.tv_sec * 1000000) + (StartTime.tv_usec);

	/* ON MET LE COUVERT */
	pthread_mutex_t **tab_mutex;
	pthread_mutex_t *current_mutex;
	
	tab_mutex = (pthread_mutex_t **) malloc(sizeof(pthread_mutex_t *) * (number_of_philo + 1));
	i = 0;
	while (i < number_of_philo)
	{
		current_mutex = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t));
		if (current_mutex == NULL)
			return (0);
		pthread_mutex_init(current_mutex, NULL);
		tab_mutex[i] = current_mutex;
		i++;
	}
	tab_mutex[i] = NULL;

	//pthread_mutex_lock(tab_mutex[0]);
	//pthread_mutex_unlock(tab_mutex[0]);

	/* ON INSTALLE LES PHILOSOPHES AUTOUR DE LA TABLE */
	tab_philo = (t_philo **) malloc(sizeof(t_philo *) * (number_of_philo + 1));
	if (tab_philo == NULL)
		return (0);

	i = 0;
	while (i < number_of_philo)
	{
		current_philo = (t_philo *) malloc(sizeof(t_philo));
		if (current_philo == NULL)
			return (0);
		current_philo->id = i;
		current_philo->start_time = start_time;
		current_philo->last_eat = 0;
		current_philo->time_to_die = time_to_die * 1000;
		current_philo->time_to_sleep = time_to_sleep * 1000;
		current_philo->time_to_eat = time_to_eat * 1000;
		current_philo->chopstick0 = tab_mutex[i];
		current_philo->chopstick1 = tab_mutex[(i+1) % number_of_philo];
		tab_philo[i] = current_philo;
		i++;
	}
	tab_philo[i] = NULL;

	//ft_print_tab_philo(tab_philo);

	/* ON COMMENCE LE REPAS */
	i = 0;
	while (i < number_of_philo)
	{
		pthread_create(&(tab_philo[i]->tid), NULL, routine_philosopher, tab_philo[i]);
		i++;
	}
	
	i = 0;
	while (i < number_of_philo)
	{
		pthread_join(tab_philo[i]->tid, NULL);
		i++;
	}



	return 0;
}