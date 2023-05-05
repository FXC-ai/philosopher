#include "philo.h"

void	init_priority(t_philo	*philo, int nb_of_philo)
{
	
	if (nb_of_philo % 2 == 0)
	{
		philo->priority = philo->id % 2;
	}
	else
	{

	}




}

int main ()
{
	int			number_of_philo;
	time_t		time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	//int	number_of_eat;
	int	i;
	//pthread_t	pid_thread_manager;
	t_manager	tab_manager;

	t_philo	**tab_philo;
	t_philo	*current_philo;

	time_t	start_time;

	number_of_philo = 3;
	time_to_sleep = 200;
	time_to_eat = 200;
	time_to_die = 400;

	/* QUELLE HEURE EST-IL ? */
	start_time = ft_time();

	/* ON MET LE COUVERT */
	pthread_mutex_t **tab_mutex;
	pthread_mutex_t *current_mutex;
	
	tab_mutex = (pthread_mutex_t **) malloc(sizeof(pthread_mutex_t *) * (number_of_philo + 1));
	i = 0;
	while (i < number_of_philo)
	{
		current_mutex = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t));
		if (current_mutex == NULL)
			return (0);
		pthread_mutex_init(current_mutex, NULL);
		tab_mutex[i] = current_mutex;
		i++;
	}
	tab_mutex[i] = NULL;

	pthread_mutex_t	**tab_mutex_protectors;

	tab_mutex_protectors = (pthread_mutex_t **) malloc(sizeof(pthread_mutex_t *) * (number_of_philo + 1));
	i = 0;
	while (i < number_of_philo)
	{
		current_mutex = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t));
		if (current_mutex == NULL)
			return (0);
		pthread_mutex_init(current_mutex, NULL);
		tab_mutex_protectors[i] = current_mutex;
		//printf("Ta maman : %p\n", tab_mutex);
		i++;
	}
	tab_mutex_protectors[i] = NULL;

	/* ON INSTALLE LES PHILOSOPHES AUTOUR DE LA TABLE */
	tab_philo = (t_philo **) malloc(sizeof(t_philo *) * (number_of_philo + 1));
	if (tab_philo == NULL)
		return (0);

	i = 0;
	while (i < number_of_philo)
	{
		current_philo = (t_philo *) malloc(sizeof(t_philo));
		if (current_philo == NULL)
			return (0);
		current_philo->id = i;
		current_philo->number_of_philo = number_of_philo;
		current_philo->start_time = start_time;
		current_philo->time_last_eat = 0;
		current_philo->mut_protect_priority = tab_mutex_protectors[i];
		current_philo->stop = 0;
		current_philo->is_dead = 0;
		current_philo->chopstick_right = tab_mutex[i];
		current_philo->chopstick_left = tab_mutex[(i+1) % number_of_philo];
		current_philo->number_of_philo = number_of_philo;
		current_philo->time_to_die = time_to_die * 1000;
		current_philo->time_to_sleep = time_to_sleep * 1000;
		current_philo->time_to_eat = time_to_eat * 1000;
		current_philo->priority = -1;
		tab_philo[i] = current_philo;
		i++;
	}
	tab_philo[i] = NULL;


	i = 0;
	while (i < number_of_philo - 1)
	{
		tab_philo[i]->priority = i % 2;
		i++;
	}
	tab_philo[i]->priority = 2;

	tab_manager.tab_philo = tab_philo;
	tab_manager.tab_mutex = tab_mutex;
	tab_manager.nb_philo = number_of_philo;


	//ft_print_tab_philo(tab_philo);

	/* ON COMMENCE LE REPAS */	
	i = 0;
	while (i < number_of_philo)
	{
		pthread_create(&(tab_philo[i]->tid), NULL, routine_philosopher, tab_philo[i]);
		i++;
	}

	//pthread_create(&pid_thread_manager, NULL, routine_manager, &tab_manager);

	//ft_print_tab_philo(tab_philo);

	i = 0;
	while (i < number_of_philo)
	{
		pthread_join(tab_philo[i]->tid, NULL);
		i++;
	}
	
	//pthread_join(pid_thread_manager, NULL);

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