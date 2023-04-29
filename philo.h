#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define EAT 1
#define SLEEP 2
#define THINK 3

typedef struct s_philo 
{

	pthread_t		tid;
	int				id;
	int				number_of_philo;
	time_t			start_time;
	int				is_dead;
	int				stop;

	pthread_mutex_t	**tab_chopstick;
	pthread_mutex_t	*chopstick_right;
	pthread_mutex_t	*chopstick_left;

	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;

	time_t			time_last_eat;
	time_t			period_last_eat;

} t_philo;

typedef struct s_manager
{
	t_philo 		**tab_philo;
	pthread_mutex_t	**tab_mutex;

} t_manager;

/*utils.c*/
void	ft_print_tab_philo (t_philo **tab_philo);
void	ft_print_tab_mutex (pthread_mutex_t **tab_mutex);
time_t	calculate_current_time_ms (time_t start_time_ms);
time_t	ft_time(void);
void	ft_usleep(time_t time_in_ms);
int     check_death(t_philo *philo);

/*routine.c*/
void	take_right_fork(t_philo *philo);
void	take_left_fork(t_philo *philo);
void	take_a_fork(t_philo *philo);
void	eat(t_philo *philo);
void	leave_right_fork(t_philo *philo);
void	leave_left_fork(t_philo *philo);
void	have_a_nape(t_philo *philo);
void    *routine_philosopher(void *philo);

#endif