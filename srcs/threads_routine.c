/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 19:20:52 by ragolden          #+#    #+#             */
/*   Updated: 2026/06/22 21:24:32 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *action)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_mut);
	if (is_dead(philo->data) && ft_strlen(action) != 4)
	{
		pthread_mutex_unlock(&philo->data->print_mut);
		return ;
	}
	timestamp = get_time() - philo->data->start_time;
	printf("%lld %d %s\n", timestamp, philo->philo_id, action);
	pthread_mutex_unlock(&philo->data->print_mut);
}

int	start_simulation(t_element *data, t_philo *philos)
{
	int	i;

	data->start_time = get_time();
	i = 0;
	while (i < data->nb_philo)
	{
		philos[i].last_meal = data->start_time;
		if (pthread_create(&philos[i].thread, NULL, philo_routine,
				&philos[i]) != 0)
			return (1);
		i++;
	}
	monitor_simulation(data, philos);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	return (0);
}

void	*single_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, FORK);
	ft_usleep(philo->data->time_to_die, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, FORK);
	pthread_mutex_lock(&philo->meal_mut);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mut);
	print_action(philo, EAT);
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->data->nb_philo == 1)
		return (single_philo_routine(philo));
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo->data->time_to_eat, philo->data);
	if (philo->philo_id == 3)
		ft_usleep(philo->data->time_to_eat * 2, philo->data);
	while (!is_dead(philo->data))
	{
		philo_eat(philo);
		print_action(philo, SLEEP);
		ft_usleep(philo->data->time_to_sleep, philo->data);
		print_action(philo, THINK);
		if (philo->data->nb_philo % 2 != 0)
			ft_usleep(philo->data->time_to_eat, philo->data);
	}
	return (NULL);
}
