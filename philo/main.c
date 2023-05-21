/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:17:44 by fcoindre          #+#    #+#             */
/*   Updated: 2023/05/21 17:42:10 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_start_time_philo(t_philo **tab_philo)
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

static void	launch_simulator(t_philo **t_phl, int nb_philos)
{
	int	i;

	i = 0;
	init_start_time_philo(t_phl);
	while (i < nb_philos)
	{
		pthread_create(&(t_phl[i]->tid), NULL, routine_philosopher, t_phl[i]);
		i++;
	}
	i = 0;
	while (i < nb_philos)
	{
		pthread_join(t_phl[i]->tid, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	time_t			tab_times[3];
	t_rules			*rules;
	t_philo			**tab_philo;
	pthread_mutex_t	**tab_chopstick;
	int				nb_philo_meals[2];

	if (parse_args(argc, argv) == 0)
		return (0);
	nb_philo_meals[0] = ft_atoi(argv[1]);
	tab_times[0] = ft_atoi(argv[2]);
	tab_times[1] = ft_atoi(argv[3]);
	tab_times[2] = ft_atoi(argv[4]);
	if (argc == 5)
		nb_philo_meals[1] = -1;
	else
		nb_philo_meals[1] = ft_atoi(argv[5]);
	rules = init_rules(nb_philo_meals[0], tab_times, nb_philo_meals[1]);
	tab_chopstick = create_tab_mutex(rules->number_of_philo);
	tab_philo = create_tab_philosophers(tab_chopstick, rules);
	launch_simulator(tab_philo, rules->number_of_philo);
	free_tab_mutex(tab_chopstick);
	free_rules(rules);
	free_tab_philo(tab_philo);
	return (0);
}
