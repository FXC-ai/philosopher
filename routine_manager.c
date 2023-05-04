#include "philo.h"

void	*routine_manager(void *tab_manager)
{

	t_manager		*cpy_tab_manager;
	//pthread_mutex_t	**cpy_tab_mutex;
	t_philo			**cpy_tab_philo;
	int				i;
	int				check_stops;

	cpy_tab_manager = (t_manager *) tab_manager;
	cpy_tab_philo = cpy_tab_manager->tab_philo;
	//cpy_tab_mutex = cpy_tab_manager->tab_mutex;

	i = 0;
	while (cpy_tab_philo[i] != NULL)
	{
		cpy_tab_philo[i]->stop = 0;
		i++;
	}

	check_stops = 0;
	while (1)
	{
		i = 0;
		while (cpy_tab_philo[i] != NULL)
		{
			check_stops += cpy_tab_philo[i]->is_dead;
			if (check_stops != 0)
			{
				printf("We have a death check_stop = %d\n", check_stops);
				i = 0;
				while (cpy_tab_philo[i] != NULL)
				{	
					cpy_tab_philo[i]->stop = 1;
					i++;
				}
				return (NULL);
			}

			pthread_mutex_lock(cpy_tab_philo[i]->mut_protect_priority);
			cpy_tab_philo[i]->priority = cpy_tab_philo[i]->priority + 1 % 3;
			pthread_mutex_unlock(cpy_tab_philo[i]->mut_protect_priority);


			i++;
		}
	}

	/*
	int i;
	int	check_stops;

	while (1)
	{
		i = 0;
		while (cpy_tab_philo[i] != NULL)
		{
			check_stops += cpy_tab_philo[i]->is_dead;
			if (check_stops != 0)
			{
				printf("check_stop = %d\n", check_stops);


				return (NULL);
			}


			i++;
		}
	}
	*/
	return NULL;
}