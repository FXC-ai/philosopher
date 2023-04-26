#include <pthread.h>
#include <stdio.h>
#define MAX 21000


typedef struct s_test_philo {

	int *count;
	int id_thread;

} t_test_philo;


void *routine(void *test_philo)
{
	t_test_philo *cpy_test_philo = (t_test_philo *) test_philo;
	int i;

	printf("Début de processus pour le thread : %d\n", cpy_test_philo->id_thread);
	
	i = 0;
	while (i < MAX)
	{
		(*(cpy_test_philo->count))++;
		//printf("WHAT %d\n", *cpy_ptr_value);
		i++;
	}
	printf("Fin de processus %d pour le thread %d\n", *(cpy_test_philo->count), cpy_test_philo->id_thread);
	
	return (NULL);
}



int main()
{
	pthread_t	tid1;
	pthread_t	tid2;

	int shared_value;
	shared_value = 0;
	
	t_test_philo	test_philo;
	test_philo.count = &shared_value;
	test_philo.id_thread = 1;
	
	t_test_philo	test_philo2;
	test_philo2.count = &shared_value;
	test_philo2.id_thread = 2;
	
	pthread_create(&tid1, NULL, routine, &test_philo);
	pthread_create(&tid2, NULL, routine, &test_philo2);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	printf("shared value = %d\n", shared_value);

	return 0;
}