#include <pthread.h>
#include <stdio.h>


void *routine(void *value)
{
	int *cpy_ptr_value = value;
	int cpy_value;
	cpy_value = *cpy_ptr_value;

	printf("Une citation quelconque  %d\n", cpy_value);
	return (NULL);

}
void *routine2(void *value)
{
	int *cpy_ptr_value = value;
	int cpy_value;
	cpy_value = *cpy_ptr_value;

	printf("Vivre et laisser mourir  %d\n", cpy_value);
	return (NULL);

}



int main()
{
	pthread_t	tid1;
	pthread_t	tid2;

	int	thread_1;
	int	thread_2;

	thread_1 = 1;
	thread_2 = 2;

	pthread_create(&tid1, NULL, routine, &thread_1);
	pthread_create(&tid2, NULL, routine2, &thread_2);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);


	return 0;
}