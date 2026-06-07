/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:23:24 by ragolden          #+#    #+#             */
/*   Updated: 2026/06/02 14:40:11 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_element
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	long long		start_time;
	int				dead_flag;
	pthread_mutex_t	dead_mut;
	pthread_mutex_t	print_mut;
	pthread_mutex_t	*forks;
}					t_element;

typedef struct s_philo
{
	int				philo_id;
	int				meals_eaten;
	long long		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mut;
	t_element		*data;
	pthread_t		thread;
}					t_philo;

# define DIE "died"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define END_MSG "All philosophers ate enough"

/*====== Utils ======*/
long long			ft_atoi(char *str);
int					ft_strlen(char *str);
void				ft_putstr_fd(int fd, char *str);
int					is_dead(t_element *data);
void				clean_all(t_element *data, t_philo *philos);

/*====== Parsing ======*/
void				error_msg(void);
int					good_format(char **av);

/*====== Init ======*/
t_philo				*init_philos(t_element *data);
int					init_global_mutexes(t_element *data);
int					init_global_data(t_element *data, int ac, char **av);

/*====== Time Gestion ======*/
long long			get_time(void);
void				ft_usleep(long long time_in_ms, t_element *data);

/*====== Threads Routine ======*/
void				print_action(t_philo *philo, char *action);
int					start_simulation(t_element *data, t_philo *philos);
void				*philo_routine(void *pointer);

/*====== Monitor ======*/
void				monitor_simulation(t_element *data, t_philo *philos);
int					check_philo_death(t_philo *philo);
int					check_meals(t_element *data, t_philo *philos);

#endif