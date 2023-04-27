#include <pthread.h>
#include <stdio.h>
#define MAX 21000


typedef struct s_test_philo {
	
	int				count;
	pthread_mutex_t	lock_01;
	pthread_mutex_t	lock_02;

} t_test_philo;


void *routine_thread1 (void *test_philo)
{
	t_test_philo *cpy_test_philo = (t_test_philo *) test_philo;
	// int i;

	printf("Le thread 1 veut bloquer le lock1\n");
	pthread_mutex_lock(&(cpy_test_philo->lock_01));
	printf("Le thread 1 bloque le lock1\n");

	printf("Le thread 1 veut bloquer le lock2\n");
	pthread_mutex_lock(&(cpy_test_philo->lock_02));
	printf("Le thread 1 bloque le lock2\n");

	cpy_test_philo->count += 1;

	printf("Le thread 1 veut debloquer le lock2\n");
	pthread_mutex_unlock(&(cpy_test_philo->lock_02));
	printf("Le thread 1 debloque le lock2\n");

	printf("Le thread 1 veut debloquer le lock1\n");
	pthread_mutex_unlock(&(cpy_test_philo->lock_01));
	printf("Le thread 1 debloque le lock1\n");

	printf("TERMINE POUR LE THREAD 1\n\n");

	return (NULL);
}

void *routine_thread2 (void *test_philo)
{
	t_test_philo *cpy_test_philo = (t_test_philo *) test_philo;
	// int i;


	printf("Le thread 2 veut bloquer le lock2\n");
	pthread_mutex_lock(&(cpy_test_philo->lock_02)); //le script  attendra jusqu' a ce que le mutex soit blocable
	printf("Le thread 2 bloque le lock2\n");

	printf("Le thread 2 veut bloquer le lock1\n");
	pthread_mutex_lock(&(cpy_test_philo->lock_01));
	printf("Le thread 2 bloque le lock1\n");

	cpy_test_philo->count += 1;

	printf("Le thread 2 veut debloquer le lock1\n");
	pthread_mutex_unlock(&(cpy_test_philo->lock_01));
	printf("Le thread 2 debloque le lock1\n");

	printf("Le thread 2 veut debloquer le lock2\n");
	pthread_mutex_unlock(&(cpy_test_philo->lock_02));
	printf("Le thread 2 debloque le lock2\n");

	printf("TERMINE POUR LE THREAD 2\n\n");

	return (NULL);
}

int main()
{
	pthread_t	tid1;
	pthread_t	tid2;
	
	t_test_philo	test_philo;
	test_philo.count = 0;
	pthread_mutex_init(&(test_philo.lock_01), NULL);
	pthread_mutex_init(&(test_philo.lock_02), NULL);

	pthread_create(&tid1, NULL, routine_thread1, &test_philo);
	pthread_create(&tid2, NULL, routine_thread2, &test_philo);

	pthread_join(tid2, NULL);
	pthread_join(tid1, NULL);

	printf("shared value = %d\n", test_philo.count);

	pthread_mutex_destroy(&test_philo.lock_01);
	pthread_mutex_destroy(&test_philo.lock_02);

	return 0;
}