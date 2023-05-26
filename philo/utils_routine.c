/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:27:14 by fcoindre          #+#    #+#             */
/*   Updated: 2023/05/26 16:13:02 by fcoindre         ###   ########.fr       */
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
