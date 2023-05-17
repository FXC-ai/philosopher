#include "philo.h"

int	check_death(t_philo *philo, int c)
{
	if (c == 1)
	{
		printf("\n%d (calculate_current_time_ms(philo->start_time) %ld - philo->time_last_eat %ld = %ld %ld\n", philo->id, calculate_current_time_ms(philo->start_time), philo->time_last_eat, (calculate_current_time_ms(philo->start_time) - philo->time_last_eat), philo->rules->time_to_die);
	}
	//sleep(2);
	if ((calculate_current_time_ms(philo->start_time) - philo->time_last_eat) > philo->rules->time_to_die)
	{
		//printf("Periode deces : %ld\n", calculate_current_time_ms(philo->start_time) - philo->time_last_eat);
	    pthread_mutex_lock(philo->mut_death);
		philo->is_dead = 1;
	    pthread_mutex_unlock(philo->mut_death);

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

int	read_priority (t_philo	*philo)
{
	int	result;

	pthread_mutex_lock(philo->mut_protect_priority);
	result = philo->priority;
	pthread_mutex_unlock(philo->mut_protect_priority);
	return (result);
}

int	check_stop (t_philo	*philo)
{
	int	result;

	pthread_mutex_lock(philo->mut_stop);
	result = philo->stop;
	pthread_mutex_unlock(philo->mut_stop);

	return (result);
}


void	eat(t_philo *philo)
{
    if (check_death(philo ,0) == 0 && check_stop(philo) == 0)
    {
		
		if (check_death(philo, 0) == 0)
		{
	    	pthread_mutex_lock(philo->chopstick_right);
	    	printf("%ld %d has taken a fork\n", calculate_current_time_ms(philo->start_time), philo->id);
		}

		if (check_death(philo, 0) == 0)
		{
        	pthread_mutex_lock(philo->chopstick_left);
        	printf("%ld %d has taken a fork\n",calculate_current_time_ms(philo->start_time), philo->id);
		}

		if (check_death(philo, 0) == 0)
		{
        	printf("\033[1;3%dm%ld %d is eating\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id);
        	philo->time_last_eat = calculate_current_time_ms(philo->start_time);
			ft_usleep(philo->rules->time_to_eat);
		}

		if (check_death(philo, 0) == 0)
		{
			philo->nb_of_eat += 1;
			if (check_nb_meals(philo) == 1)
			{
				pthread_mutex_lock(philo->mut_stop);
				philo->stop = 1;
				pthread_mutex_unlock(philo->mut_stop);
			}
		}

		if (check_death(philo, 0) == 0)
		{
			pthread_mutex_lock(philo->mut_protect_priority);
			philo->priority = 0;
			pthread_mutex_unlock(philo->mut_protect_priority);
		}

		if (check_death(philo, 0) == 0)
		{
        	pthread_mutex_unlock(philo->chopstick_right);
			pthread_mutex_unlock(philo->chopstick_left);
		}
    }
}

void	have_a_nape(t_philo *philo)
{
    if (check_death(philo, 0) == 0 && check_stop(philo) == 0)
    {
		printf("%ld %d is sleeping\n", calculate_current_time_ms(philo->start_time),philo->id);
		ft_usleep(philo->rules->time_to_sleep);
	}
}

void	think(t_philo *philo)
{
    if (check_death(philo, 0) == 0 && check_stop(philo) == 0)
    {
		printf("%ld %d is thinking\n", calculate_current_time_ms(philo->start_time),philo->id);
	}
}

void *routine_philosopher(void *philo)
{
	t_philo			*cpy_philo;

	cpy_philo = (t_philo *) philo;

	while (42)
	{
		
		if (read_priority(cpy_philo) == 1 && check_nb_meals(cpy_philo) == 0)
		{
			eat(cpy_philo); 
			have_a_nape(cpy_philo);
			think(cpy_philo);
		}

		if (check_stop(cpy_philo) == 1)
		{
			break;
		}

		if (check_death(cpy_philo, 0) == 1 && check_nb_meals(cpy_philo) == 0)
		{
			printf("\033[1;3%dm%ld %d died\n\033[0m", cpy_philo->id % 7, calculate_current_time_ms(cpy_philo->start_time),cpy_philo->id);
			//ft_print_philo(cpy_philo);
			break;
		}
		if (check_nb_meals(cpy_philo) == 1)
		{
			pthread_mutex_lock(cpy_philo->mut_stop);
			cpy_philo->stop = 1;
			pthread_mutex_unlock(cpy_philo->mut_stop);
			break;
		}
		
	}
	return NULL;
}
