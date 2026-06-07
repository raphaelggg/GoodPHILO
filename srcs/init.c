/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:32:57 by ragolden          #+#    #+#             */
/*   Updated: 2026/05/29 17:34:57 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_global_mutexes(t_element *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->dead_mut, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->print_mut, NULL) != 0)
		return (1);
	return (0);
}

int	init_global_data(t_element *data, int ac, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
	else
		data->nb_meals = -1;
	if (data->nb_philo <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (1);
	if (ac == 6 && data->nb_meals <= 0)
		return (1);
	data->dead_flag = 0;
	return (init_global_mutexes(data));
}

static void	assign_forks(t_philo *philo, t_element *data, int i)
{
	if (i % 2 == 0)
	{
		philo->left_fork = &data->forks[i];
		philo->right_fork = &data->forks[(i + 1) % data->nb_philo];
	}
	else
	{
		philo->left_fork = &data->forks[(i + 1) % data->nb_philo];
		philo->right_fork = &data->forks[i];
	}
}

t_philo	*init_philos(t_element *data)
{
	int		i;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		philos[i].philo_id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = 0;
		philos[i].data = data;
		if (pthread_mutex_init(&philos[i].meal_mut, NULL) != 0)
			return (NULL);
		assign_forks(&philos[i], data, i);
		i++;
	}
	return (philos);
}
