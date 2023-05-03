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
	int				number_of_philo;
	time_t			start_time;
	int				is_dead;
	int				keep;

	pthread_mutex_t	**tab_chopstick;
	pthread_mutex_t	*chopstick_right;
	pthread_mutex_t	*chopstick_left;

	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;

	time_t			time_last_eat;
	time_t			period_last_eat;

} t_philo;

void	ft_print_tab_philo (t_philo **tab_philo)
{
	int	i;

	i = 0;
	while (tab_philo[i] != NULL)
	{
		printf("        id = [%d]\n", tab_philo[i]->id);
		printf("start_time = [%ld]\n", tab_philo[i]->start_time);
		printf("fork_right = [%p]\n", tab_philo[i]->chopstick_right);
		printf("fork_left  = [%p]\n", tab_philo[i]->chopstick_left);
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

time_t	ft_time(void)
{
	struct		timeval	tv;
	time_t		time_in_mils;

	gettimeofday(&tv, NULL);
	time_in_mils = tv.tv_sec * 1000000 + (tv.tv_usec);
	return (time_in_mils);
}

void	ft_usleep(time_t time_in_ms)
{
	time_t	current_time;

	current_time = ft_time();
	while ((ft_time() - current_time) <= time_in_ms)
	{
		usleep(25);
		if ((ft_time() - current_time) >= time_in_ms)
			break ;
	}
}



void	take_right_fork(t_philo *philo)
{
	printf("\033[1;3%dm%ld ms : Philosopher %d try to take the right fork [%p].\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id, philo->chopstick_right);
	pthread_mutex_lock(philo->chopstick_right);
	printf("\033[1;3%dm%ld ms : Philosopher %d has taken the right fork [%p].\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id, philo->chopstick_right);
}

void	take_left_fork(t_philo *philo)
{
	printf("\033[1;3%dm%ld ms : Philosopher %d try to take the left fork [%p].\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id, philo->chopstick_left);
	pthread_mutex_lock(philo->chopstick_left);
	printf("\033[1;3%dm%ld ms : Philosopher %d has taken take the left fork [%p].\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id, philo->chopstick_left);
}

void	take_a_fork(t_philo *philo)
{

	if (philo->id < (philo->number_of_philo - 1))
	{
		take_right_fork (philo);
		take_left_fork(philo);
	}
	else if (philo->id == (philo->number_of_philo - 1))
	{
		take_left_fork(philo);
		take_right_fork (philo);
	}
}

void	eat(t_philo *philo)
{
	time_t current_time_eat;

	printf("\033[1;3%dm%ld ms : Philosopher %d start to eat.\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id);
	ft_usleep(philo->time_to_eat);
	current_time_eat = calculate_current_time_ms(philo->start_time);
	philo->period_last_eat = current_time_eat - philo->time_last_eat;
	//printf("current_time_eat [%ld] - philo->time_last_eat [%ld] = philo->period_last_eat [%ld]\n", current_time_eat, philo->time_last_eat, philo->period_last_eat);
	philo->time_last_eat = current_time_eat;


	//exit (42);
	printf("\033[1;3%dm%ld ms : Philosopher %d finish to eat.\n\033[0m", (philo->id % 7), current_time_eat, philo->id);

}

void	leave_right_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->chopstick_right);
	printf("\033[1;3%dm%ld ms : Philosopher %d leave the right fork.\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id);
}

void	leave_left_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->chopstick_left);
	printf("\033[1;3%dm%ld ms : Philosopher %d leave the left fork.\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id);
}

void	have_a_nape(t_philo *philo)
{
	printf("%ld ms : Philosopher %d is sleeping.\n", calculate_current_time_ms(philo->start_time),philo->id);
	ft_usleep(philo->time_to_sleep);
}

void *routine_philosopher(void *philo)
{
	t_philo			*cpy_ptr_philo;
	struct timeval	current_time;
	time_t			current_time_ms;

	int test;
	
	cpy_ptr_philo = (t_philo *) philo;

	test = 0;
	while (cpy_ptr_philo->keep == 0)
	{
		if (cpy_ptr_philo->period_last_eat < cpy_ptr_philo->time_to_die)
		{
			take_a_fork (cpy_ptr_philo);
		}
		// if (cpy_ptr_philo->period_last_eat < cpy_ptr_philo->time_to_die)
		// {	
		// 	take_left_fork(cpy_ptr_philo);
		// }
		if (cpy_ptr_philo->period_last_eat < cpy_ptr_philo->time_to_die)
		{
			eat(cpy_ptr_philo);
		}
		if (cpy_ptr_philo->period_last_eat < cpy_ptr_philo->time_to_die)
		{
			leave_right_fork(cpy_ptr_philo);	
		}
		if (cpy_ptr_philo->period_last_eat < cpy_ptr_philo->time_to_die)
		{
			leave_left_fork(cpy_ptr_philo);	
		}
		if (cpy_ptr_philo->period_last_eat < cpy_ptr_philo->time_to_die)
		{
			have_a_nape(cpy_ptr_philo);
		}
		if (cpy_ptr_philo->period_last_eat > cpy_ptr_philo->time_to_die)
		{
			cpy_ptr_philo->is_dead = 1;
			printf("Le philosophe %d est mort car il n'a pas mange depuis %ld ms.\n", cpy_ptr_philo->id, cpy_ptr_philo->period_last_eat);
			break;
		}
		//printf("For Philosopher %d last_eat = %ld\n", cpy_ptr_philo->id ,cpy_ptr_philo-> last_eat);

		printf("%ld ms : Philosopher %d is thinking.\n", calculate_current_time_ms(cpy_ptr_philo->start_time),(*cpy_ptr_philo).id);

		//printf("%ld ms : Philosopher %d is dead.\n", calculate_current_time_ms(cpy_ptr_philo->start_time),(*cpy_ptr_philo).id);
		//test ++;
	}
	return NULL;
}


void	*ft_thread_manager(void *tab_philo)
{
	t_philo **cpy_tab_philo;
	cpy_tab_philo = (t_philo **) tab_philo;
	int i;
	int j;
	int	check_keeps;

	while (1)
	{
		i = 0;
		while (cpy_tab_philo[i] != NULL)
		{
			check_keeps += cpy_tab_philo[i]->is_dead;
			if (check_keeps != 0)
			{
				printf("check_keep = %d\n", check_keeps);
				j = 0;
				while (cpy_tab_philo[j] != NULL)
				{
					cpy_tab_philo[j]->keep = 1;
					j++;
				}

				return (NULL);
			}


			i++;
		}
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

	number_of_philo = 3;
	time_to_sleep = 200;
	time_to_eat = 200;
	time_to_die = 400;

	//ft_usleep(1000*1000);

	/* QUELLE HEURE EST-IL ? */
	// gettimeofday(&StartTime, NULL);
	start_time = ft_time();

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
		current_philo->number_of_philo = number_of_philo;
		current_philo->start_time = start_time;
		current_philo->time_last_eat = 0;
		current_philo->keep = 0;
		current_philo->is_dead = 0;
		current_philo->time_to_die = time_to_die * 1000;
		current_philo->time_to_sleep = time_to_sleep * 1000;
		current_philo->time_to_eat = time_to_eat * 1000;
		current_philo->chopstick_right = tab_mutex[i];
		current_philo->chopstick_left = tab_mutex[(i+1) % number_of_philo];
		tab_philo[i] = current_philo;
		i++;
	}
	tab_philo[i] = NULL;


	
	pthread_t pid_thread_manager;

	pthread_create(&pid_thread_manager, NULL, ft_thread_manager, tab_philo);

	/* ON COMMENCE LE REPAS */
	i = 0;
	while (i < number_of_philo)
	{
		pthread_create(&(tab_philo[i]->tid), NULL, routine_philosopher, tab_philo[i]);
		i++;
	}
	
	//ft_print_tab_philo(tab_philo);




	i = 0;
	while (i < number_of_philo)
	{
		pthread_join(tab_philo[i]->tid, NULL);
		i++;
	}
	
	pthread_join(pid_thread_manager, NULL);

	i = 0;
	while (i < number_of_philo)
	{
		pthread_mutex_destroy(tab_mutex[i]);
		i++;
	}

	return 0;
}