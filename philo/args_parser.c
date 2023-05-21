/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:29:01 by fcoindre          #+#    #+#             */
/*   Updated: 2023/05/21 17:39:24 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isnumeric(char *str)
{
	while (*str != '\0')
	{
		if (ft_isdigit(*str) == 0)
		{
			return (0);
		}
		str++;
	}
	return (1);
}

int	check_four_args(char **argv)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (ft_isnumeric(argv[i]) == 0 || ft_atoi(argv[i]) > 2147483647)
			return (0);
		i++;
	}
	return (1);
}

int	check_fifth_arg(char **argv)
{
	if (ft_isnumeric(argv[5]) == 1 && ft_atoi(argv[5]) < 2147483647)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	parse_args(int argc, char *argv[])
{
	if (argc < 5)
	{
		return (0);
	}
	if (argc >= 5)
	{
		if (check_four_args(argv) == 0)
		{
			return (0);
		}
		if (argc > 5)
		{
			if (check_fifth_arg(argv) == 0)
			{
				return (0);
			}
		}
	}
	return (1);
}
