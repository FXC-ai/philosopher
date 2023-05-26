/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:17:44 by fcoindre          #+#    #+#             */
/*   Updated: 2023/05/26 17:28:39 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_rules (t_rules *rules)
{
	printf("number_of_philo = %d\n", rules->number_of_philo);
	printf("            die : %ld | eat : %ld | sleep : %ld\n", rules->time_to_die, rules->time_to_eat, rules->time_to_sleep);
	printf("     nb_of_meal = %d\n", rules->nb_of_meal);
	printf("            end = %d\n", rules->end);
	printf("        mut_end = %p\n", rules->mut_end);
	//printf("   mut_tot_meal = %p\n", rules->mut_tot_meals);
}

void	ft_print_philo (t_philo *philo)
{
	printf("           id = [%d]\n", philo->id + 1);
	printf("   start_time = [%ld]\n", philo->start_time);

	printf("mt_fork_right = [%p]\n", philo->chopstick_right);
	printf(" mt_fork_left = [%p]\n", philo->chopstick_left);

	printf("chstick right = [%d]\n", philo->for_right);
	printf("chstick left  = [%d]\n", philo->for_left);
	printf("      is_dead = [%d]\n", philo->is_dead);
	printf("time last eat = [%ld]\n", philo->time_last_eat);
	printf("\n");
	ft_print_rules(philo->rules);
	printf("------------------------------------------------\n");
}

void	ft_print_tab_philo (t_philo **tab_philo)
{
	int	i;

	i = 0;
	while (tab_philo[i] != NULL)
	{
		ft_print_philo(tab_philo[i]);
		i++;
	}
}

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

pthread_t	*create_tab_of_tid(t_philo **tab_philo, int nb_of_philos)
{
	int	i;
	pthread_t	*result;

	result = (pthread_t *) malloc(sizeof(pthread_t));
	if (result == NULL)
		return (NULL);

	i = 0;
	while (i < nb_of_philos)
	{
		result[i] = tab_philo[i]->tid;
		i++;
	}
	return (result);
}

static void	launch_simulator(t_philo **t_phl, int nb_philos, t_rules *rules)
{
	int	i;
	int	stop;
	(void) rules;
	//int	max_meals;
	//printf("nb_philo = %d\n", nb_philos);

	pthread_t	*tab_tid;

	tab_tid = create_tab_of_tid(t_phl, nb_philos);

	//max_meals = nb_philos * rules->nb_of_meal;
	//printf("max_meals = %d\n", max_meals);
	stop = 0;
	i = 0;
	init_start_time_philo(t_phl);
	while (i < nb_philos)
	{
		pthread_create(&(t_phl[i]->tid), NULL, routine_philosopher, t_phl[i]);
		i++;
	}
	
	i = 0;
	while (42)
	{
		if (i == rules->number_of_philo)
			i = 0;

		if (check_death(t_phl[i]) == 1)
		{
			break;
		}
		i++;
	}

	i = 0;
	while (i < nb_philos)
	{
		//printf("i = %d\n", i);
		pthread_join(tab_tid[i], NULL);
		//printf("Confirm\n");
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

	//ft_print_tab_philo(tab_philo);
	//return (0);

	launch_simulator(tab_philo, rules->number_of_philo, rules);


	//ft_print_tab_philo(tab_philo);

	free_tab_mutex(tab_chopstick);
	free_rules(rules);
	free_tab_philo(tab_philo);
	return (0);
}
