#include "philo.h"

void	*routine_manager(void *tab_manager)
{
	t_manager		*cpy_tab_manager;
	t_philo			**cpy_tab_philo;
	int				id_tour;
	int				id_philo;
	int				nb_philo;
	int				check_priorities;
	//int				check_deaths;

	id_tour = 1;
	check_priorities = 0;
	//check_deaths = 0;
	
	cpy_tab_manager = (t_manager *) tab_manager;
	cpy_tab_philo = cpy_tab_manager->tab_philo;

	nb_philo = cpy_tab_manager->rules->number_of_philo;

	while (42)
	{
		id_philo = 0;
		check_priorities = 0;

		while (cpy_tab_philo[id_philo] != NULL)
		{
			pthread_mutex_lock(cpy_tab_philo[id_philo]->mut_protect_priority);
			check_priorities += cpy_tab_philo[id_philo]->priority;
			pthread_mutex_unlock(cpy_tab_philo[id_philo]->mut_protect_priority);

			/*
			pthread_mutex_lock(cpy_tab_philo[id_philo]->mut_death);
			check_deaths += cpy_tab_philo[id_philo]->is_dead;
			if (check_deaths > 0)
			{
				pthread_mutex_unlock(cpy_tab_philo[id_philo]->mut_death);
				break;
			}
			pthread_mutex_unlock(cpy_tab_philo[id_philo]->mut_death);
			*/
			id_philo++;
		}

		/*
		if (check_deaths > 0)
		{
			id_philo = 0;
			while (cpy_tab_philo[id_philo] != NULL)
			{
				printf("%ld ms : NOW\n", calculate_current_time_ms(cpy_tab_philo[id_philo]->start_time));
				pthread_mutex_lock(cpy_tab_philo[id_philo]->mut_protect_priority);
				cpy_tab_philo[id_philo]->priority = 0;
				pthread_mutex_unlock(cpy_tab_philo[id_philo]->mut_protect_priority);
				id_philo++;
			}
			return NULL;
		}
		*/

		if (check_priorities == 0)
		{
			id_philo = 0;
			while (cpy_tab_philo[id_philo] != NULL)
			{
				pthread_mutex_lock(cpy_tab_philo[id_philo]->mut_protect_priority);
				cpy_tab_philo[id_philo]->priority = ((id_tour + cpy_tab_philo[id_philo]->id) % nb_philo) % 2;
				pthread_mutex_unlock(cpy_tab_philo[id_philo]->mut_protect_priority);
				id_philo++;
			}
			id_tour++;
		}
	}
	return NULL;
}