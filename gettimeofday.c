/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:17:17 by fcoindre          #+#    #+#             */
/*   Updated: 2023/04/25 17:42:50 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>

int main ()
{

	struct timeval currentTime;
	struct timeval initTime;

	int tmp;
	int	i;


	gettimeofday(&initTime, NULL);

	printf("start_time = %ld\n", initTime.tv_sec);

	tmp = 0;
	i = 0;
	while (currentTime.tv_sec < initTime.tv_sec + 10)
	{
		gettimeofday(&currentTime, NULL);
		if (currentTime.tv_sec != tmp)
		{
			printf("i = %d\n", i);
			tmp = currentTime.tv_sec;
			i++;
		}
	}



	

	return 0;
}