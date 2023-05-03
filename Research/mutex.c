#include <pthread.h>
#include <stdio.h>
#define MAX 21000


typedef struct s_test_philo {

	int				count;
	pthread_mutex_t	count_mutex;

} t_test_philo;


void *routine(void *test_philo)
{
	t_test_philo *cpy_test_philo = (t_test_philo *) test_philo;
	int i;

	printf("Début de processus %d\n", cpy_test_philo->count);
	
	i = 0;
	while (i < MAX)
	{
		pthread_mutex_lock(&cpy_test_philo->count_mutex);
		(cpy_test_philo->count)++;
		pthread_mutex_unlock(&cpy_test_philo->count_mutex);
		i++;
	}
	printf("Fin de processus %d\n", cpy_test_philo->count);
	return (NULL);
}

int main()
{
	pthread_t	tid1;
	pthread_t	tid2;
	
	t_test_philo	test_philo;
	test_philo.count = 0;
	pthread_mutex_init(&(test_philo.count_mutex), NULL);

	pthread_create(&tid1, NULL, routine, &test_philo);
	pthread_create(&tid2, NULL, routine, &test_philo);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	printf("shared value = %d\n", test_philo.count);

	pthread_mutex_destroy(&test_philo.count_mutex);

	return 0;
}
