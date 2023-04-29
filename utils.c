#include "philo.h"

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

