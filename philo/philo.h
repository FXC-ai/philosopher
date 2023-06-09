/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:33:23 by fcoindre          #+#    #+#             */
/*   Updated: 2023/05/28 13:35:24 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_rules
{
	int				number_of_philo;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				nb_of_meal;
	int				end;

	pthread_mutex_t	*mut_end;
}	t_rules;

typedef struct s_philo
{
	pthread_t		tid;

	pthread_mutex_t	*chopstick_right;
	pthread_mutex_t	*chopstick_left;
	pthread_mutex_t	*mut_dead;

	time_t			start_time;
	time_t			time_last_eat;

	int				id;
	int				number_of_philo;
	int				is_dead;
	int				nb_of_eat;
	int				chopstick_taken;
	int				for_right;
	int				for_left;

	t_rules			*rules;

}	t_philo;

/* philo_creators.c */
pthread_mutex_t	**create_tab_mutex(int n);
t_rules			*init_rules(int nb_of_ph, time_t *tab_times, int nb_of_meal);
t_philo			**create_tab_philosophers(pthread_mutex_t **t_ck, t_rules *rls);
pthread_mutex_t	*mutex_creator(void);

/* free_philos.c */
void			free_tab_mutex(pthread_mutex_t **tab_mutex);
void			free_tab_philo(t_philo **tab_philo);
void			free_rules(t_rules *rules);
void			free_mut_ends(t_philo **tab_philo);

/* args_parser.c */
int				ft_isdigit(int c);
int				ft_isnumeric(char *str);
int				check_four_args(char **argv);
int				check_fifth_arg(char **argv);
int				parse_args(int argc, char *argv[]);

/* utils.c */
time_t			calculate_current_time_ms(time_t start_time_ms);
time_t			ft_time(void);
void			ft_usleep(time_t time_in_ms, t_philo *philo);

/* utils_philo.c */
int				read_end(t_philo *philo);
int				read_dead(t_philo *philo);
void			set_is_dead(t_philo *philo);
void			set_end(t_philo *philo);
int				check_nb_meals(t_philo *philo);

/* utils_philo2.c */
void			take_right_chopstick(t_philo *philo);
void			take_left_chopstick(t_philo *philo);
void			have_a_nape(t_philo *philo);
void			think(t_philo *philo);

/* routine_philo.c */
int				check_death(t_philo *philo);
void			eat(t_philo *philo);
void			*routine_philosopher(void *philo);

long			ft_atoi(const char *str);
#endif