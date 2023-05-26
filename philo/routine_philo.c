/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:17:31 by fcoindre          #+#    #+#             */
/*   Updated: 2023/05/26 11:44:36 by fcoindre         ###   ########.fr       */
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

int read_dead(t_philo *philo)
{
	int result;

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

// void	add_meal_to_total(t_philo *philo)
// {
// 	//printf("je rentre philo = %d\n", philo->id);
// 	pthread_mutex_lock(philo->rules->mut_tot_meals);
// 	philo->rules->tot_meals += 1;
// 	pthread_mutex_unlock(philo->rules->mut_tot_meals);
// 	//printf("je sors philo = %d\n", philo->id);
// }

int	check_death(t_philo *philo)
{
	//int c1;
	//int c2;

	if ((calculate_current_time_ms(philo->start_time) - philo->time_last_eat)
		> philo->rules->time_to_die)
	{
		if (read_dead(philo) == 0 && read_end(philo) == 0 && check_nb_meals(philo) == 0)
		{
			set_is_dead(philo);
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
	if (read_end(philo) == 0 && philo->chopstick_taken == 0)
	{
		//printf("chopstick_taken = %d\n", philo->chopstick_taken);
		pthread_mutex_lock(philo->chopstick_right);
		philo->chopstick_taken += 1;
		//printf("chopstick_taken = %d\n", philo->chopstick_taken);
		if (read_end(philo) == 0)
		{
			printf("%ld %d has taken a fork\n",
				calculate_current_time_ms(philo->start_time),
				philo->id + 1);
		}
		//printf("%d Je debloque la R\n", philo->id + 1);

	}
}

void	take_left_chopstick(t_philo *philo)
{
	if (read_end(philo) == 0 && philo->rules->number_of_philo > 1) //ATTENTION BIEN UTILE D UTILISER LE 2EME CHECK ????
	{
		//printf("Je bloque la L\n");
		pthread_mutex_lock(philo->chopstick_left);
		philo->chopstick_taken += 1;
		if (read_end(philo) == 0)
		{
			printf("%ld %d has taken a fork\n",
				calculate_current_time_ms(philo->start_time), philo->id + 1);
		}
		//printf("Je debloque la L\n");

	}
}

void	eat(t_philo *philo)
{
	if (read_end(philo) == 0)
	{
		take_right_chopstick(philo);
		take_left_chopstick(philo);
		if (read_end(philo) == 0 && philo->chopstick_taken == 2)
		{
			printf("%ld %d is eating\n",
				calculate_current_time_ms(philo->start_time), philo->id + 1);
			philo->time_last_eat = calculate_current_time_ms(philo->start_time);
			ft_usleep(philo->rules->time_to_eat, philo);
		}
		if (read_end(philo) == 0 && philo->rules->number_of_philo > 1)
		{
			philo->nb_of_eat += 1;
			//add_meal_to_total(philo);
		}
		if (philo->rules->number_of_philo > 1)
		{
			philo->chopstick_taken = 0;
			pthread_mutex_unlock(philo->chopstick_right);
			pthread_mutex_unlock(philo->chopstick_left);
		}
	}
}

void	have_a_nape(t_philo *philo)
{
	if (read_end(philo) == 0 && check_nb_meals(philo) == 0 && philo->rules->number_of_philo > 1)
	{
		printf("%ld %d is sleeping\n",
			calculate_current_time_ms(philo->start_time), philo->id + 1);
		ft_usleep(philo->rules->time_to_sleep, philo);
	}
}

void	think(t_philo *philo)
{
	if (read_end(philo) == 0
		&& check_nb_meals(philo) == 0 && philo->rules->number_of_philo > 1)
	{
		if (read_end(philo) == 0)
		{
			printf("%ld %d is thinking\n",
				calculate_current_time_ms(philo->start_time), philo->id + 1);
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
		{
			break ;
		}
		if (read_end(cpy_philo) == 1)
		{
			//printf("%d : stopped\n", cpy_philo->id);
			break;
		}
		// if (check_death (cpy_philo) == 1)
		// {
		// 	break ;
		// }
	}
	printf("Philo %d : PROCESS ENDED\n", cpy_philo->id + 1);
	return (NULL);
}
