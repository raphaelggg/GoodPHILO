/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:45:29 by ragolden          #+#    #+#             */
/*   Updated: 2026/06/22 23:19:12 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_simulation(t_element *data, t_philo *philos)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (check_philo_death(&philos[i]))
				return ;
			i++;
		}
		if (data->nb_meals != -1)
		{
			if (check_meals(data, philos) == 1)
				return ;
		}
		usleep(1000);
	}
}

int	check_philo_death(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->meal_mut);
	time = get_time() - philo->last_meal;
	if (time > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->dead_mut);
		philo->data->dead_flag = 1;
		pthread_mutex_unlock(&philo->data->dead_mut);
		print_action(philo, DIE);
		pthread_mutex_unlock(&philo->meal_mut);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mut);
	return (0);
}

int	check_meals(t_element *data, t_philo *philos)
{
	int	finished_eating_count;
	int	philo_count;

	finished_eating_count = 0;
	philo_count = 0;
	while (philo_count < data->nb_philo)
	{
		pthread_mutex_lock(&philos[philo_count].meal_mut);
		if (philos[philo_count].meals_eaten >= data->nb_meals)
			finished_eating_count++;
		pthread_mutex_unlock(&philos[philo_count].meal_mut);
		philo_count++;
	}
	if (finished_eating_count == data->nb_philo)
	{
		pthread_mutex_lock(&data->dead_mut);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->dead_mut);
		print_action(&philos[0], END_MSG);
		return (1);
	}
	return (0);
}
