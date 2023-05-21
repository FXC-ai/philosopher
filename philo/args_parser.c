/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:29:01 by fcoindre          #+#    #+#             */
/*   Updated: 2023/05/21 13:29:11 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isnumeric (char *str)
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
