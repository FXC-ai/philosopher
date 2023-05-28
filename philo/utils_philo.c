/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:09:51 by fcoindre          #+#    #+#             */
/*   Updated: 2023/05/28 13:15:57 by fcoindre         ###   ########.fr       */
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

int	read_dead(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(philo->mut_dead);
	result = philo->rules->end;
	pthread_mutex_unlock(philo->mut_dead);
	return (result);
}

void	set_is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->mut_dead);
	philo->is_dead = 1;
	pthread_mutex_unlock(philo->mut_dead);
}

void	set_end(t_philo *philo)
{
	pthread_mutex_lock(philo->rules->mut_end);
	philo->rules->end = 1;
	pthread_mutex_unlock(philo->rules->mut_end);
}

int	check_nb_meals(t_philo *philo)
{
	if (philo->nb_of_eat == philo->rules->nb_of_meal)
	{
		return (1);
	}
	return (0);
}
