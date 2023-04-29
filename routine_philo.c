#include "philo.h"

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

	printf("\033[1;3%dm%ld ms : Philosopher %d start to eat.\n\033[0m", (philo->id % 7),calculate_current_time_ms(philo->start_time), philo->id);
	ft_usleep(philo->time_to_eat);
	philo->time_last_eat = calculate_current_time_ms(philo->start_time);
	printf("\033[1;3%dm%ld ms : Philosopher %d finish to eat.\n\033[0m", (philo->id % 7), philo->time_last_eat, philo->id);
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
	
	cpy_ptr_philo = (t_philo *) philo;

	while (cpy_ptr_philo->stop == 0)
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
