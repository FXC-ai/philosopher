/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:53:00 by fcoindre          #+#    #+#             */
/*   Updated: 2023/05/21 13:55:57 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char a);
static int	ft_space_min_finder(const char *str, int *is_negativ);

static int	ft_isspace(char a)
{
	if (a == ' '
		|| a == '\f'
		|| a == '\n'
		|| a == '\r'
		|| a == '\t'
		|| a == '\v')
	{
		return (1);
	}
	return (0);
}

static int	ft_space_min_finder(const char *str, int *is_negativ)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			*is_negativ *= -1;
		}
		i++;
	}
	return (i);
}

long	ft_atoi(const char *str)
{
	int		i;
	int		is_negativ;
	long	result;
	long	multiplier;

	multiplier = 1;
	result = 0;
	is_negativ = 1;
	i = ft_space_min_finder(str, &is_negativ);
	while (str[i] >= '0' && str[i] <= '9')
	{
		i++;
	}
	i--;
	while (i != -1 && (str[i] >= '0' && str[i] <= '9'))
	{
		result += (str[i] - 48) * multiplier;
		multiplier *= 10;
		i--;
	}
	return (result * is_negativ);
}
