
#include <stdio.h>

int main()
{
	int i;
	int nb_tour;
	int	id_philo;
	int nb_philo;

	nb_tour = 0;
	nb_philo = 5;

	while (nb_tour < 5)
	{
		printf("Tour %d\n", nb_tour);
		id_philo = 0;
		while (id_philo < nb_philo)
		{
			if (id_philo != nb_philo)
			{
				printf("id_philo = %d => %d\n", id_philo, (nb_tour + id_philo) % 2);
			}
			else
			{
				printf("id_philo = %d => %d\n", id_philo, (nb_tour +1) % 2);
			}
			
			id_philo++;
		}

		printf("\n");
		
		nb_tour++;
	}


}