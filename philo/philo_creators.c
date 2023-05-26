/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:23:32 by fcoindre          #+#    #+#             */
/*   Updated: 2023/05/25 16:31:21 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	**create_tab_mutex(int n)
{
	pthread_mutex_t	**t_chstck;
	pthread_mutex_t	*current_mutex;
	int				i;

	t_chstck = (pthread_mutex_t **) malloc(sizeof(pthread_mutex_t *) * (n + 1));
	i = 0;
	while (i < n)
	{
		current_mutex = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t));
		if (current_mutex == NULL)
			return (NULL);
		pthread_mutex_init(current_mutex, NULL);
		t_chstck[i] = current_mutex;
		i++;
	}
	t_chstck[i] = NULL;
	return (t_chstck);
}

t_rules	*init_rules(int number_of_philo, time_t *tab_times, int number_of_meal)
{
	pthread_mutex_t	*cur_mut_end;
	t_rules			*rules;

	rules = (t_rules *) malloc (sizeof(t_rules));
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
	rules->tot_meals = 0;
	rules->end = 0;
	pthread_mutex_init(cur_mut_end, NULL);
	rules->mut_end = cur_mut_end;
	rules->mut_tot_meals = mutex_creator();
	return (rules);
}

void	init_consts_philo(t_philo *cur_phl)
{
	cur_phl->start_time = 0;
	cur_phl->time_last_eat = 0;
	cur_phl->chopstick_taken = 0;
	cur_phl->is_dead = 0;
}

pthread_mutex_t	*mutex_creator()
{
	pthread_mutex_t	*result;

	result = (pthread_mutex_t *) malloc(sizeof(pthread_t));
	if (result == NULL)
		return (NULL);
	pthread_mutex_init(result, NULL);
	//printf("%p : mutex control\n", result);
	return (result);
}


t_philo	**create_tab_philosophers(pthread_mutex_t **t_chopstick, t_rules *rules)
{
	t_philo			**t_p;
	t_philo			*cur_phl;
	int				i;
	pthread_mutex_t	**tab_chopstick;

	tab_chopstick = create_tab_mutex(rules->number_of_philo);
	t_p = (t_philo **) malloc(sizeof(t_philo *) * (rules->number_of_philo + 1));
	if (t_p == NULL)
		return (0);
	i = 0;
	while (i < rules->number_of_philo)
	{
		cur_phl = (t_philo *) malloc(sizeof(t_philo));
		if (cur_phl == NULL)
			return (0);
		init_consts_philo(cur_phl);
		cur_phl->id = i;
		cur_phl->mut_dead = mutex_creator();
		cur_phl->chopstick_right = t_chopstick[i];
		cur_phl->chopstick_left = t_chopstick[(i + 1) % rules->number_of_philo];
		cur_phl->rules = rules;
		t_p[i] = cur_phl;
		i++;
	}
	t_p[i] = NULL;
	return (t_p);
}
