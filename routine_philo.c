#include "philo.h"

int	check_death(t_philo *philo)
{

	//printf("\n (calculate_current_time_ms(philo->start_time) %ld - philo->time_last_eat %ld = %ld %ld\n",calculate_current_time_ms(philo->start_time), philo->time_last_eat, (calculate_current_time_ms(philo->start_time) - philo->time_last_eat), philo->time_to_die);
	if ((calculate_current_time_ms(philo->start_time) - philo->time_last_eat) > philo->rules->time_to_die)
	{
		//printf("Le philosophe %d est mort.\n", philo->id);
		philo->is_dead = 1;
		return (1);
	}
	return (0);
}

void	take_right_fork(t_philo *philo)
{
    if (check_death(philo) == 0 && philo->stop == 0)
    {
	    printf("\033[1;3%dm%ld ms : Philosopher %d try to take the right fork [%p].\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id, philo->chopstick_right);
	    pthread_mutex_lock(philo->chopstick_right);
	    printf("\033[1;3%dm%ld ms : Philosopher %d has taken the right fork [%p].\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id, philo->chopstick_right);
    }
}

void	take_left_fork(t_philo *philo)
{
    if (check_death(philo) == 0 && philo->stop == 0)
    {
        printf("\033[1;3%dm%ld ms : Philosopher %d try to take the left fork [%p].\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id, philo->chopstick_left);
        pthread_mutex_lock(philo->chopstick_left);
        printf("\033[1;3%dm%ld ms : Philosopher %d has taken the left fork [%p].\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id, philo->chopstick_left);
    }
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
    if (check_death(philo) == 0 && philo->stop == 0)
    {
        printf("\033[1;3%dm%ld ms : Philosopher %d start to eat.\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id);
        ft_usleep(philo->rules->time_to_eat);
        philo->time_last_eat = calculate_current_time_ms(philo->start_time);
		philo->nb_of_meal += 1;
		philo->has_eaten = 1;
		pthread_mutex_lock(philo->mut_protect_priority);
		philo->priority = 0;
		pthread_mutex_unlock(philo->mut_protect_priority);


        printf("\033[1;3%dm%ld ms : Philosopher %d finish to eat.\n\033[0m", (philo->id % 7), philo->time_last_eat, philo->id);
    }
}

void	put_right_fork(t_philo *philo)
{

    if (check_death(philo) == 0 && philo->stop == 0)
    {
        pthread_mutex_unlock(philo->chopstick_right);
        printf("\033[1;3%dm%ld ms : Philosopher %d leave the right fork.\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id);
    }

}

void	put_left_fork(t_philo *philo)
{
	if (check_death(philo) == 0 && philo->stop == 0)
    {
		pthread_mutex_unlock(philo->chopstick_left);
		printf("\033[1;3%dm%ld ms : Philosopher %d leave the left fork.\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id);
	}
}

void	have_a_nape(t_philo *philo)
{
    if (check_death(philo) == 0 && philo->stop == 0)
    {
		printf("\033[1;3%dm%ld ms : Philosopher %d is sleeping.\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time),philo->id);
		ft_usleep(philo->rules->time_to_sleep);
	}
}

void	think(t_philo *philo)
{
    if (check_death(philo) == 0 && philo->stop == 0)
    {
		printf("\033[1;3%dm%ld ms : Philosopher %d is thinking.\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time),philo->id);
	}
}

int		read_priority (t_philo	*philo)
{
	int	result;

	pthread_mutex_lock(philo->mut_protect_priority);
	result = philo->priority;
	pthread_mutex_unlock(philo->mut_protect_priority);
	return (result);
}


void *routine_philosopher(void *philo)
{
	t_philo			*cpy_philo;

	cpy_philo = (t_philo *) philo;
	while (42)
	{
		
		if (cpy_philo->priority == 1)
		{
			take_right_fork (cpy_philo);
			take_left_fork(cpy_philo);
			eat(cpy_philo); 
			put_right_fork(cpy_philo);	
			put_left_fork(cpy_philo);	
			have_a_nape(cpy_philo);
			think(cpy_philo);

		}
		
		if (cpy_philo->is_dead == 1)
		{
			printf("%ld ms : Philosopher %d is dead.\n", calculate_current_time_ms(cpy_philo->start_time),cpy_philo->id);
			break;
		}
	}
	return NULL;
}

/*
int main ()
{
	int	number_of_philo;
	time_t time_to_die;
	int time_to_eat;
	int time_to_sleep;
	//int	number_of_eat;
	int	i;

	t_philo	**tab_philo;
	t_philo	*current_philo;

	time_t	start_time;

	number_of_philo = 4;
	time_to_sleep = 200;
	time_to_eat = 200;
	time_to_die = 190;


	start_time = ft_time();


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
		current_philo->time_last_eat = 0;
		current_philo->stop = 0;
		current_philo->is_dead = 0;
		current_philo->chopstick_right = tab_mutex[i];
		current_philo->chopstick_left = tab_mutex[(i+1) % number_of_philo];


		current_philo->number_of_philo = number_of_philo;
		current_philo->time_to_die = time_to_die * 1000;
		current_philo->time_to_sleep = time_to_sleep * 1000;
		current_philo->time_to_eat = time_to_eat * 1000;
		tab_philo[i] = current_philo;
		i++;
	}
	tab_philo[i] = NULL;

	//check_death(tab_philo[0]);


	routine_philosopher(tab_philo[0]);

	return 0;
}
*/