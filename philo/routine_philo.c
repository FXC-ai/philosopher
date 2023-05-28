/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:17:31 by fcoindre          #+#    #+#             */
/*   Updated: 2023/05/28 13:28:11 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	if ((calculate_current_time_ms(philo->start_time) - philo->time_last_eat)
		> philo->rules->time_to_die)
	{
		if (read_dead(philo) == 0 && read_end(philo) == 0
			&& check_nb_meals(philo) == 0)
		{
			set_is_dead(philo);
			printf("\033[1;31m%ld %d died\n\033[0m",
				calculate_current_time_ms(philo->start_time), philo->id + 1);
		}
		set_end(philo);
		if (philo->for_right == 1)
		{
			pthread_mutex_unlock(philo->chopstick_right);
			philo->for_right = 0;
		}
		if (philo->for_left == 1)
		{
			pthread_mutex_unlock(philo->chopstick_left);
			philo->for_left = 0;
		}
		return (1);
	}
	return (0);
}

static void	put_right_chpostick(t_philo *philo)
{
	pthread_mutex_unlock(philo->chopstick_right);
	philo->for_right = 0;
}

void	eat(t_philo *philo)
{
	if (read_end(philo) == 0)
	{
		take_right_chopstick(philo);
		take_left_chopstick(philo);
		if (read_end(philo) == 0 && philo->for_left == 1
			&& philo->for_right == 1)
		{
			printf("%ld %d is eating\n",
				calculate_current_time_ms(philo->start_time), philo->id + 1);
			philo->time_last_eat = calculate_current_time_ms(philo->start_time);
			ft_usleep(philo->rules->time_to_eat, philo);
		}
		if (read_end(philo) == 0 && philo->rules->number_of_philo > 1)
			philo->nb_of_eat += 1;
		if (philo->rules->number_of_philo > 1)
		{
			if (philo->for_right == 1)
				put_right_chpostick(philo);
			if (philo->for_left == 1)
			{
				pthread_mutex_unlock(philo->chopstick_left);
				philo->for_left = 0;
			}
		}
	}
}

void	*routine_philosopher(void *philo)
{
	t_philo			*cpy_philo;

	cpy_philo = (t_philo *) philo;
	if (cpy_philo->id % 2 == 1)
	{
		ft_usleep((cpy_philo->rules->time_to_eat / 2), philo);
	}
	while (42)
	{
		if (check_nb_meals(cpy_philo) == 0)
		{
			eat(cpy_philo);
			have_a_nape(cpy_philo);
			think(cpy_philo);
		}
		if (check_nb_meals (cpy_philo) == 1)
			break ;
		if (read_end(cpy_philo) == 1)
			break ;
	}
	return (NULL);
}
