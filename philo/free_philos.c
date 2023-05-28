/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:30:36 by fcoindre          #+#    #+#             */
/*   Updated: 2023/05/28 13:34:07 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_tab_mutex(pthread_mutex_t **tab_mutex)
{
	int	i;

	i = 0;
	while (tab_mutex[i] != NULL)
	{
		pthread_mutex_destroy(tab_mutex[i]);
		free(tab_mutex[i]);
		i++;
	}
	free (tab_mutex);
}

void	free_mut_ends(t_philo **tab_philo)
{
	int	i;

	i = 0;
	while (tab_philo[i] != NULL)
	{
		pthread_mutex_destroy(tab_philo[i]->mut_dead);
		free (tab_philo[i]->mut_dead);
		i++;
	}
}

void	free_tab_philo(t_philo **tab_philo)
{
	int	i;

	i = 0;
	while (tab_philo[i] != NULL)
	{
		free(tab_philo[i]);
		i++;
	}
	free (tab_philo);
}

void	free_rules(t_rules *rules)
{
	pthread_mutex_destroy(rules->mut_end);
	free (rules->mut_end);
	free (rules);
}
