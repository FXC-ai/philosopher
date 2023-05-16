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

typedef struct s_rules
{
	int			number_of_philo;
	time_t		time_to_die;
	time_t		time_to_eat;
	time_t		time_to_sleep;
	int			nb_of_meal;
} t_rules;

typedef struct s_philo 
{

	pthread_t		tid;
	int				id;
	int				number_of_philo;
	time_t			start_time;
	int				is_dead;
	int				stop;
	int				priority;
	int				nb_of_eat;

	pthread_mutex_t	*mut_protect_priority;
	pthread_mutex_t *mut_stop;
	pthread_mutex_t *mut_death;

	//pthread_mutex_t	**tab_chopstick;
	pthread_mutex_t	*chopstick_right;
	pthread_mutex_t	*chopstick_left;

	time_t			time_last_eat;
	time_t			period_last_eat;


	t_rules			*rules;


} t_philo;

typedef struct s_manager
{
	t_philo **tab_philo;
	t_rules	*rules;

} t_manager;



/*utils.c*/
void	ft_print_rules (t_rules *rules);
void	ft_print_tab_philo (t_philo **tab_philo);
void	ft_print_philo (t_philo *philo);

void	ft_print_tab_mutex (pthread_mutex_t **tab_mutex);
time_t	calculate_current_time_ms (time_t start_time_ms);
time_t	ft_time(void);
void	ft_usleep(time_t time_in_ms);
int     check_death(t_philo *philo, int c);

/*routine_philo.c*/
void	take_right_fork(t_philo *philo);
void	take_left_fork(t_philo *philo);
void	take_a_fork(t_philo *philo);
void	eat(t_philo *philo);
void	put_right_fork(t_philo *philo);
void	put_left_fork(t_philo *philo);
void	have_a_nape(t_philo *philo);
void    *routine_philosopher(void *philo);
int		read_priority(t_philo	*philo);

void	*routine_manager(void *tab_manager);

long	ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_isnumeric (char *str);

#endif