#include "philo.h"

int	read_end (t_philo *philo)
{
	int	result;

	pthread_mutex_lock(philo->rules->mut_end);
	result = philo->rules->end;
	pthread_mutex_unlock(philo->rules->mut_end );

	return (result);
}


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
		if (philo->is_dead == 0 && read_end(philo) == 0)
		{
			philo->is_dead = 1;
			printf("\033[1;3%dm%ld %d died\n\033[0m", philo->id % 7, calculate_current_time_ms(philo->start_time), philo->id);
		}

		pthread_mutex_lock(philo->rules->mut_end);		
		if (philo->rules->end == 0)
		{
			philo->rules->end = 1;
			//printf("Je viens de set end a 1\n");
		}
		pthread_mutex_unlock(philo->rules->mut_end);

		pthread_mutex_unlock(philo->chopstick_right);
		pthread_mutex_unlock(philo->chopstick_left);

		return (1);
	}
	return (0);
	//return (philo->is_dead);
}

int	check_nb_meals(t_philo *philo)
{
	if (philo->nb_of_eat == philo->rules->nb_of_meal)
	{
		return (1);
	}
	return (0);
}

void	eat(t_philo *philo)
{
    if (check_death(philo ,0) == 0 && read_end(philo) == 0)
    {
		
		if (check_death(philo, 0) == 0 && read_end(philo) == 0)
		{
	    	//ft_print_philo(philo);
	    	pthread_mutex_lock(philo->chopstick_right);
			philo->chopstick_taken += 1;
	    	printf("%ld %d has taken a fork\n", calculate_current_time_ms(philo->start_time), philo->id);
		}

		if (check_death(philo, 0) == 0 && read_end(philo) == 0)
		{
	    	//printf("%ld %d try to take a fork (left)\n", calculate_current_time_ms(philo->start_time), philo->id);
        	pthread_mutex_lock(philo->chopstick_left);
			philo->chopstick_taken += 1;
        	printf("%ld %d has taken a fork\n",calculate_current_time_ms(philo->start_time), philo->id);
		}

		if (check_death(philo, 0) == 0 && read_end(philo) == 0 && philo->chopstick_taken == 2)
		{
        	printf("\033[1;3%dm%ld %d is eating\n\033[0m", (philo->id % 7), calculate_current_time_ms(philo->start_time), philo->id);
			philo->time_last_eat = calculate_current_time_ms(philo->start_time);
			ft_usleep(philo->rules->time_to_eat, philo);
		}

		if (check_death(philo, 0) == 0 && read_end(philo) == 0)
		{
			philo->nb_of_eat += 1;
		}

		if (check_death(philo, 0) == 0 && read_end(philo) == 0)
		{
			philo->chopstick_taken = 0;
        	pthread_mutex_unlock(philo->chopstick_right);
			pthread_mutex_unlock(philo->chopstick_left);
		}
    }
}

void	have_a_nape(t_philo *philo)
{
    if (check_death(philo, 0) == 0 && read_end(philo) == 0 && check_nb_meals(philo) == 0)
    {
		printf("%ld %d is sleeping\n", calculate_current_time_ms(philo->start_time),philo->id);
		ft_usleep(philo->rules->time_to_sleep, philo);
	}
}

void	think(t_philo *philo)
{
    if (check_death(philo, 0) == 0 && read_end(philo) == 0 && check_nb_meals(philo) == 0)
    {
		printf("%ld %d is thinking\n", calculate_current_time_ms(philo->start_time),philo->id);
	}
}

void *routine_philosopher(void *philo)
{
	t_philo			*cpy_philo;

	cpy_philo = (t_philo *) philo;

	if (cpy_philo->id % 2 == 1)
	{
		ft_usleep((cpy_philo->rules->time_to_eat / 2), philo);
	}

	while (42)
	{
		//printf("%d je tourne toujours\n", cpy_philo->id);
		
		if (check_nb_meals(cpy_philo) == 0)
		{
			eat(cpy_philo); 
			have_a_nape(cpy_philo);
			think(cpy_philo);
		}

		if (check_nb_meals(cpy_philo) == 1)
		{

			break;
		}

		if (check_death(cpy_philo, 0) == 1)
		{
			//printf("\033[1;3%dm%ld %d died\n\033[0m", cpy_philo->id % 7, calculate_current_time_ms(cpy_philo->start_time),cpy_philo->id);
			//ft_print_philo(cpy_philo);
			break;
		}


		
	
		
	}


	return NULL;
}

/*
DANS QUEL ORDRE DOIVENT SE FAIRE LES CHECK ????
FAIRE UN CHECK SUR LA VARIABLE END !!!

ET SI IL MEURT EN MANGEANT ???????

*/