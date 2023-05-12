
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


time_t	calculate_current_time_ms (time_t start_time_ms)
{
	struct timeval current_time;
	time_t	current_time_ms;
	time_t	result;

	gettimeofday(&current_time, NULL);
	current_time_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	result = current_time_ms - start_time_ms;
	return (result);
}

time_t	ft_time(void)
{
	struct		timeval	tv;
	time_t		time_in_mils;

	gettimeofday(&tv, NULL);
	time_in_mils = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
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

int main()
{
	int id_philo;
	int	nb_philo;
	int id_tour;
	int nb_tour;


	printf("ft_time = %ld\n", ft_time());

	time_t test = ft_time();
	ft_usleep(200);
	printf("ft_time = %ld\n", calculate_current_time_ms(test));


	nb_philo = 3;
	nb_tour = 5;

	id_tour = 0;
	while (id_tour < nb_tour)
	{
		printf("Tour %d\n", id_tour);
		id_philo = 0;
		while (id_philo < nb_philo)
		{			
			printf("id_philo = %d => %d\n", id_philo, ((id_tour + id_philo) % nb_philo) % 2);
			id_philo++;
		}
		printf("\n");	
		id_tour++;
	}
}