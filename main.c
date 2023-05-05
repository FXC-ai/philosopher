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
	t_rules	*s_rules = (t_rules *)	malloc (sizeof(t_rules));
	if (s_rules == NULL)
		return NULL;

	s_rules->number_of_philo = number_of_philo;
	s_rules->time_to_die = tab_times[0];
	s_rules->time_to_eat = tab_times[1];
	s_rules->time_to_sleep = tab_times[2];
	s_rules->number_of_meal = number_of_meal;

	return (s_rules);
}

t_philo	**create_tab_philosophers(pthread_mutex_t **tab_chopstick, pthread_mutex_t **tab_mutex_priority, t_rules *rules)
{
	t_philo		**tab_philo;
	t_philo		*current_philo;
	int			i;

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
		current_philo->stop = 0;
		current_philo->is_dead = 0;
		
		current_philo->chopstick_right = tab_chopstick[i];
		current_philo->chopstick_left = tab_chopstick[(i+1) % rules->number_of_philo];
		current_philo->mut_protect_priority = tab_mutex_priority[i];

		current_philo->priority = -1;

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


int main ()
{
	//int			number_of_philo = 5;
	//int			number_of_meals = 3;

	time_t			tab_times[3];
	t_rules			*rules;
	t_philo			**tab_philo;
	pthread_mutex_t	**tab_mutex_protectors;
	pthread_mutex_t **tab_mutex_nbmeal;
	pthread_mutex_t **tab_chopstick;
	int				i;
	t_manager		tab_manager;
	//pthread_t	pid_thread_manager;


	tab_times[0] = 410; //time_to_die
	tab_times[1] = 200; //time_to_eat
	tab_times[2] = 200; //time_to_sleep

	/* ON DONNE LES REGLES */
	rules = init_rules(2, tab_times, 5);

	/* ON MET LE COUVERT */
	tab_chopstick = create_tab_mutex(rules->number_of_philo);

	tab_mutex_protectors = create_tab_mutex(rules->number_of_philo);

	tab_mutex_nbmeal = create_tab_mutex(rules->number_of_philo);

	/* ON INSTALLE LES PHILOSOPHES AUTOUR DE LA TABLE */
	tab_philo = create_tab_philosophers(tab_chopstick, tab_mutex_protectors, rules);

	init_start_time_philo(tab_philo);

	//ft_print_tab_philo(tab_philo);


	tab_manager.tab_philo = tab_philo;
	tab_manager.rules = rules;
	// tab_manager.tab_mutex = tab_chopstick;
	// tab_manager.nb_philo = rules->number_of_philo;

	/* ON COMMENCE LE REPAS */	
	i = 0;
	while (i < rules->number_of_philo)
	{
		pthread_create(&(tab_philo[i]->tid), NULL, routine_philosopher, tab_philo[i]);
		i++;
	}

	// pthread_create(&pid_thread_manager, NULL, routine_manager, &tab_manager);

	//ft_print_tab_philo(tab_philo);


	i = 0;
	while (i < rules->number_of_philo)
	{
		pthread_join(tab_philo[i]->tid, NULL);
		i++;
	}
	
	// pthread_join(pid_thread_manager, NULL);

	/*
	i = 0;
	while (i < number_of_philo)
	{
		pthread_mutex_destroy(tab_mutex[i]);
		i++;
	}
	*/
	return 0;
}