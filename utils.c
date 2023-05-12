#include "philo.h"



void	ft_print_philo (t_philo *philo)
{

	printf("           id = [%d]\n", philo->id);
	printf("   start_time = [%ld]\n", philo->start_time);
	printf("   fork_right = [%p]\n", philo->chopstick_right);
	printf("    fork_left = [%p]\n", philo->chopstick_left);
	printf("protect_prior = [%p]\n", philo->mut_protect_priority);
	printf("\033[1;32m     priority = [%d]\n\033[0m", philo->priority);
	printf("      is_dead = [%d]\n", philo->is_dead);
	printf("         stop = [%d]\n", philo->stop);
	printf("time last eat = [%ld]\n", philo->time_last_eat);
	printf("prid last eat = [%ld]\n", philo->period_last_eat);
	printf("\n");
}

void	ft_print_tab_philo (t_philo **tab_philo)
{
	int	i;

	i = 0;
	while (tab_philo[i] != NULL)
	{
		ft_print_philo(tab_philo[i]);
		
		i++;
	}

}
/*
void	ft_print_tab_mutex()
{

}
*/
void	ft_print_tab_mutex (pthread_mutex_t **tab_mutex)
{
	int	i;

	i = 0;
	while (tab_mutex[i] != NULL)
	{
		printf("[%d] (%p)\n", i, tab_mutex[i]);
		i++;
	}
}

time_t	calculate_current_time_ms (time_t start_time_ms)
{
	struct timeval current_time;
	time_t	current_time_ms;
	time_t	result;

	gettimeofday(&current_time, NULL);
	current_time_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec/1000);
	result = current_time_ms - start_time_ms;
	return (result);
}

time_t	ft_time(void)
{
	struct		timeval	tv;
	time_t		time_in_mils;

	gettimeofday(&tv, NULL);
	time_in_mils = tv.tv_sec * 1000 + (tv.tv_usec/1000);
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


