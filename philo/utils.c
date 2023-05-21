/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:17:20 by fcoindre          #+#    #+#             */
/*   Updated: 2023/05/21 14:02:27 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	calculate_current_time_ms(time_t start_time_ms)
{
	struct timeval	current_time;
	time_t			cur_time_ms;
	time_t			result;

	gettimeofday(&current_time, NULL);
	cur_time_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	result = cur_time_ms - start_time_ms;
	return (result);
}

time_t	ft_time(void)
{
	struct timeval	tv;
	time_t			time_in_mils;

	gettimeofday(&tv, NULL);
	time_in_mils = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
	return (time_in_mils);
}

void	ft_usleep(time_t time_in_ms, t_philo *philo)
{
	time_t	current_time;

	current_time = ft_time();
	while ((ft_time() - current_time) <= time_in_ms)
	{
		usleep(50);
		if ((ft_time() - current_time) >= time_in_ms || check_death(philo) == 1)
			break ;
	}
}
