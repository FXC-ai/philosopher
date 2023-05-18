#include "philo.h"

pthread_mutex_t	**create_tab_mutex(int number_of_philo)
{
	pthread_mutex_t	**tab_chopstick;
	pthread_mutex_t	*current_mutex;
	int				i;

	tab_chopstick = (pthread_mutex_t **) malloc(sizeof(pthread_mutex_t *) * (number_of_philo + 1));
	i = 0;
	while (i < number_of_philo)
	{
		current_mutex = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t));
		if (current_mutex == NULL)
			return (NULL);
		pthread_mutex_init(current_mutex, NULL);
		tab_chopstick[i] = current_mutex;
		i++;
	}
	tab_chopstick[i] = NULL;

	return tab_chopstick;
}

t_rules	*init_rules (int number_of_philo, time_t *tab_times, int number_of_meal)
{
	pthread_mutex_t *cur_mut_end;
	t_rules	*rules = (t_rules *) malloc (sizeof(t_rules));
	if (rules == NULL)
		return (NULL);

	cur_mut_end = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (rules == NULL)
		return (NULL);

	rules->number_of_philo = number_of_philo;
	rules->time_to_die = tab_times[0];
	rules->time_to_eat = tab_times[1];
	rules->time_to_sleep = tab_times[2];
	rules->nb_of_meal = number_of_meal;
	rules->end = 0;
	/*
	
	ATTENTION !!!! IL FAUT INIT LE MUTEX !!!!!!!
	
	*/


	rules->mut_end = cur_mut_end;

	return (rules);
}

t_philo	**create_tab_philosophers(pthread_mutex_t **tab_chopstick, t_rules *rules)
{
	t_philo			**tab_philo;
	t_philo			*current_philo;
	int				i;

	tab_philo = (t_philo **) malloc(sizeof(t_philo *) * (rules->number_of_philo + 1));
	if (tab_philo == NULL)
		return (0);

	i = 0;
	while (i < rules->number_of_philo)
	{
		current_philo = (t_philo *) malloc(sizeof(t_philo));
		if (current_philo == NULL)
			return (0);

		current_philo->id = i;
		current_philo->start_time = 0;
		current_philo->time_last_eat = 0;
		
		current_philo->mut_stop = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
		if (current_philo->mut_stop == NULL)
			return (NULL);
		pthread_mutex_init(current_philo->mut_stop, NULL);

		//printf("TEST : %p\n", current_philo->mut_nbmeal);

		current_philo->stop = 0;


		current_philo->is_dead = 0;
		
		current_philo->chopstick_right = tab_chopstick[i];
		current_philo->chopstick_left = tab_chopstick[(i+1) % rules->number_of_philo];

		current_philo->rules = rules;


		tab_philo[i] = current_philo;
		i++;
	}
	tab_philo[i] = NULL;
	return (tab_philo);
}

void	init_start_time_philo(t_philo **tab_philo)
{
	int		i;
	time_t	start_time;

	start_time = ft_time();
	i = 0;
	while (tab_philo[i] != NULL)
	{
		tab_philo[i]->start_time = start_time;
		i++;
	}

}

/*SEPARER LES CAS PAIRS ET IMPAIRS ????

Cas limite : 15 410 200 200


*/
int main (int argc, char *argv[])
{
	time_t			tab_times[3];
	t_rules			*rules;
	t_philo			**tab_philo;

	pthread_mutex_t	**tab_mutex_protectors;
	pthread_mutex_t **tab_chopstick;

	int				i;
	t_manager		tab_manager;
	//pthread_t		pid_thread_manager;

	int				nb_philo;
	int				nb_meals;
	int				debug;

	nb_meals = -1;
	if (argc >= 5)
	{
		i = 1;
		while (i < 5)
		{
			if (ft_isnumeric(argv[i]) == 0 || ft_atoi(argv[i]) > 2147483647)
				return (1);
			i++;
		}

		nb_philo = ft_atoi(argv[1]);
		tab_times[0] = ft_atoi(argv[2]); //time_to_die
		tab_times[1] = ft_atoi(argv[3]); //time_to_eat
		tab_times[2] = ft_atoi(argv[4]); //time_to_sleep

		if (argc > 5)
		{
			if (ft_isnumeric(argv[5]) == 1 && ft_atoi(argv[5]) < 2147483647)
			{
				nb_meals = ft_atoi(argv[5]);
			}
			else
			{
				return (1);
			}
		}

	}
	else
	{
		return (1);
	}



	/* ON DONNE LES REGLES */
	rules = init_rules(nb_philo, tab_times, nb_meals);

	//ft_print_rules(rules);
	//return (404);

	/* ON MET LE COUVERT */
	tab_chopstick = create_tab_mutex(rules->number_of_philo);

	tab_mutex_protectors = create_tab_mutex(rules->number_of_philo);

	/* ON INSTALLE LES PHILOSOPHES AUTOUR DE LA TABLE */
	tab_philo = create_tab_philosophers(tab_chopstick, rules);
	// ft_print_tab_philo(tab_philo);
	// return 404;

	tab_manager.tab_philo = tab_philo;
	tab_manager.rules = rules;

	/* ON COMMENCE LE REPAS */	
	i = 0;
	init_start_time_philo(tab_philo);
	while (i < rules->number_of_philo)
	{
		//printf("Creation de philo %d\n", i);
		pthread_create(&(tab_philo[i]->tid), NULL, routine_philosopher, tab_philo[i]);
		i++;
	}

	//pthread_create(&pid_thread_manager, NULL, routine_manager, &tab_manager);

	i = 0;
	while (i < rules->number_of_philo)
	{
		debug = pthread_join(tab_philo[i]->tid, NULL);
		//printf("debug = %d | i = %d\n", debug, i);

		i++;
	}
	
	//pthread_join(pid_thread_manager, NULL);

	return 0;
}