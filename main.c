#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>

#define EAT 1
#define SLEEP 2
#define THINK 3

typedef struct s_philo {

	int id;
	int state;





} t_philo;

void *routine_philosopher(void *philo)
{
	


}


int main ()
{
	int	number_of_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int	number_of_eat;
	int	i;

	struct timeval StartTime;
	time_t start_time_sec;

	struct timeval CurrentTime;
	time_t current_time_sec;

	time_t	execution_time_sec;

	gettimeofday(&StartTime, NULL);
	start_time_sec = StartTime.tv_sec;
	printf("start_time_sec = %ld\n", start_time_sec);

	i = 0;
	while (i < 10000000)
	{
		gettimeofday(&CurrentTime, NULL);
		execution_time_sec = CurrentTime.tv_sec - StartTime.tv_sec;
		printf("current_time_sec = %ld\n", execution_time_sec);
		i++;
	}

	t_philo philo1;
	philo1.id = 1;
	philo1.state = THINK;

	t_philo philo2;
	philo2.id = 2;
	philo2.state = THINK;


	return 0;
}