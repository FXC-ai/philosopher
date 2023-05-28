/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:18:21 by fcoindre          #+#    #+#             */
/*   Updated: 2023/05/28 13:22:16 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_right_chopstick(t_philo *philo)
{
	if (read_end(philo) == 0 && philo->for_right == 0)
	{
		pthread_mutex_lock(philo->chopstick_right);
		philo->for_right = 1;
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
	if (read_end(philo) == 0 && philo->for_left == 0
		&& philo->rules->number_of_philo > 1)
	{
		pthread_mutex_lock(philo->chopstick_left);
		philo->for_left = 1;
		if (read_end(philo) == 0)
		{
			printf("%ld %d has taken a fork\n",
				calculate_current_time_ms(philo->start_time), philo->id + 1);
		}
	}
}

void	have_a_nape(t_philo *philo)
{
	if (read_end(philo) == 0 && check_nb_meals(philo) == 0
		&& philo->rules->number_of_philo > 1)
	{
		printf("%ld %d is sleeping\n",
			calculate_current_time_ms(philo->start_time), philo->id + 1);
		ft_usleep(philo->rules->time_to_sleep, philo);
	}
}

void	think(t_philo *philo)
{
	if (read_end(philo) == 0 && check_nb_meals(philo) == 0
		&& philo->rules->number_of_philo > 1)
	{
		if (read_end(philo) == 0)
		{
			printf("%ld %d is thinking\n",
				calculate_current_time_ms(philo->start_time), philo->id + 1);
		}
	}
}
