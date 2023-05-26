/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:27:14 by fcoindre          #+#    #+#             */
/*   Updated: 2023/05/21 19:00:32 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	read_end(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(philo->rules->mut_end);
	result = philo->rules->end;
	pthread_mutex_unlock(philo->rules->mut_end);
	return (result);
}

int	check_death(t_philo *philo)
{
	if ((calculate_current_time_ms(philo->start_time) - philo->time_last_eat)
		> philo->rules->time_to_die)
	{
		if (philo->is_dead == 0 && read_end(philo) == 0)
		{
			philo->is_dead = 1;
			printf("\033[1;31m%ld %d died\n\033[0m",
				calculate_current_time_ms(philo->start_time), philo->id + 1);
		}
		pthread_mutex_lock(philo->rules->mut_end);
		if (philo->rules->end == 0)
		{
			philo->rules->end = 1;
		}
		pthread_mutex_unlock(philo->rules->mut_end);
		pthread_mutex_unlock(philo->chopstick_right);
		pthread_mutex_unlock(philo->chopstick_left);
		return (1);
	}
	return (0);
}

int	check_nb_meals(t_philo *philo)
{
	if (philo->nb_of_eat == philo->rules->nb_of_meal)
	{
		return (1);
	}
	return (0);
}

void	take_right_chopstick(t_philo *philo)
{
	if (check_death(philo) == 0
		&& read_end(philo) == 0
		&& philo->chopstick_taken == 0)
	{
		pthread_mutex_lock(philo->chopstick_right);
		philo->chopstick_taken += 1;
		if (read_end(philo) == 0)
		{
			printf("%ld %d has taken a fork\n",
				calculate_current_time_ms(philo->start_time),
				philo->id + 1);
		}
	}
}

void	take_left_chopstick(t_philo *philo)
{
	if (check_death(philo) == 0
		&& read_end(philo) == 0
		&& philo->rules->number_of_philo > 1)
	{
		pthread_mutex_lock(philo->chopstick_left);
		philo->chopstick_taken += 1;
		if (read_end(philo) == 0)
		{
			printf("%ld %d has taken a fork\n",
				calculate_current_time_ms(philo->start_time), philo->id + 1);
		}
	}
}
