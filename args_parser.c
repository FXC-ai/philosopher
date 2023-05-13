include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isnumeric (char *str)
{
	while (*str != NULL)
	{
		if (ft_isdigit(*str) == 0)
		{
			return (0);
		}
		str++;
	}
	return (1);
}