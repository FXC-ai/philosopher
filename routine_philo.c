#include "philo.h"

int	check_death(t_philo *philo)
{

	//printf("\n (calculate_current_time_ms(philo->start_time) %ld - philo->time_last_eat %ld = %ld %ld\n",calculate_current_time_ms(philo->start_time), philo->time_last_eat, (calculate_current_time_ms(philo->start_time) - philo->time_last_eat), philo->rules->time_to_die);
	if ((calculate_current_time_ms(philo->start_time) - philo->time_last_eat) > philo->rules->time_to_die)
	{
		//printf("Periode deces : %ld\n", calculate_current_time_ms(philo->start_time) - philo->time_last_eat);
		philo->is_dead = 1;
		return (1);
	}
	return (0);
}

int	check_nb_meals(t_philo *philo)
{
	if (philo->nb_of_eat == philo->rules->nb_of_meal)
	{
		return (1);
	}
	return (0);
}

void	take_right_fork(t_philo *philo)
{
    if (check_death(philo) == 0)
    {
	    //printf("\033[1;3%dm%ld ms : Philosopher %d try to take the right fork [%p].\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id, philo->chopstick_right);
	    pthread_mutex_lock(philo->chopstick_right);
	    printf("\033[1;3%dm%ld ms : %d has taken a fork (right)\n\033[0m", 
				(philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id);
    }
}

void	take_left_fork(t_philo *philo)
{
    if (check_death(philo) == 0)
    {
        //printf("\033[1;3%dm%ld ms : Philosopher %d try to take the left fork [%p].\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id, philo->chopstick_left);
        pthread_mutex_lock(philo->chopstick_left);
        printf("\033[1;3%dm%ld ms : %d has taken a fork (left)\n\033[0m", 
				(philo->id % 7),
				calculate_current_time_ms(philo->start_time), philo->id);
    }
}


void	eat(t_philo *philo)
{
    if (check_death(philo) == 0)
    {
        printf("\033[1;3%dm%ld ms : %d is eating\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id);
        ft_usleep(philo->rules->time_to_eat);
        philo->time_last_eat = calculate_current_time_ms(philo->start_time);
		philo->nb_of_eat += 1;
		pthread_mutex_lock(philo->mut_protect_priority);
		philo->priority = 0;
		pthread_mutex_unlock(philo->mut_protect_priority);


        //printf("\033[1;3%dm%ld ms : Philosopher %d finish to eat.\n\033[0m", (philo->id % 7), philo->time_last_eat, philo->id);
    }
}

void	put_right_fork(t_philo *philo)
{

    if (check_death(philo) == 0)
    {
        pthread_mutex_unlock(philo->chopstick_right);
        //printf("\033[1;3%dm%ld ms : %d leave the right fork.\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id);
    }

}

void	put_left_fork(t_philo *philo)
{
	if (check_death(philo) == 0)
    {
		pthread_mutex_unlock(philo->chopstick_left);
		//printf("\033[1;3%dm%ld ms : Philosopher %d leave the left fork.\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id);
	}
}

void	have_a_nape(t_philo *philo)
{
    if (check_death(philo) == 0)
    {
		printf("\033[1;3%dm%ld ms : %d is sleeping\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time),philo->id);
		ft_usleep(philo->rules->time_to_sleep);
	}
}

void	think(t_philo *philo)
{
    if (check_death(philo) == 0)
    {
		printf("\033[1;3%dm%ld ms : %d is thinking\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time),philo->id);
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
		
		//sleep(2);
		//ft_print_philo(cpy_philo);

		if (read_priority(cpy_philo) == 1 && check_nb_meals(cpy_philo) == 0)
		{
			//printf("poire\n");
			take_right_fork (cpy_philo);
			take_left_fork(cpy_philo);
			eat(cpy_philo); 
			put_right_fork(cpy_philo);	
			put_left_fork(cpy_philo);	
			have_a_nape(cpy_philo);
			think(cpy_philo);

		}
		if (check_death(cpy_philo) == 1 && check_nb_meals(cpy_philo) == 0)
		{
			printf("%ld ms : %d died\n", calculate_current_time_ms(cpy_philo->start_time),cpy_philo->id);
			//ft_print_philo(cpy_philo);
			break;
		}
		
	}
	return NULL;
}
