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


	pthread_mutex_init(cur_mut_end, NULL);

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
		current_philo->chopstick_taken = 0;
		


		//printf("TEST : %p\n", current_philo->mut_nbmeal);



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

void	free_tab_mutex(pthread_mutex_t **tab_mutex)
{
	int i;

	i = 0;
	while (tab_mutex[i] != NULL)
	{
		pthread_mutex_destroy(tab_mutex[i]);
		free(tab_mutex[i]);
		i++;
	}
	free (tab_mutex);
}

void	free_tab_philo(t_philo **tab_philo)
{
	int i;

	i = 0;
	while (tab_philo[i] != NULL)
	{
		free(tab_philo[i]);
		i++;
	}
	free (tab_philo);
}

void	free_rules(t_rules *rules)
{
	pthread_mutex_destroy(rules->mut_end);
	free (rules->mut_end);
	free (rules);
}

int main (int argc, char *argv[])
{
	time_t			tab_times[3];
	t_rules			*rules;
	t_philo			**tab_philo;

	pthread_mutex_t **tab_chopstick;

	int				i;
	t_manager		tab_manager;


	int				nb_philo;
	int				nb_meals;

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

	/* ON MET LE COUVERT */
	tab_chopstick = create_tab_mutex(rules->number_of_philo);

	/* ON INSTALLE LES PHILOSOPHES AUTOUR DE LA TABLE */
	tab_philo = create_tab_philosophers(tab_chopstick, rules);
	
	tab_manager.tab_philo = tab_philo;
	tab_manager.rules = rules;

	//ft_print_tab_philo(tab_philo);


	/* ON COMMENCE LE REPAS */	
	i = 0;
	init_start_time_philo(tab_philo);
	while (i < rules->number_of_philo)
	{
		pthread_create(&(tab_philo[i]->tid), NULL, routine_philosopher, tab_philo[i]);
		i++;
	}

	i = 0;
	while (i < rules->number_of_philo)
	{
		pthread_join(tab_philo[i]->tid, NULL);
		i++;
	}

	free_tab_mutex(tab_chopstick);
	free_rules(rules);
	free_tab_philo(tab_philo);

	return 0;
}