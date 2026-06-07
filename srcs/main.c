/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:54:06 by ragolden          #+#    #+#             */
/*   Updated: 2026/06/02 14:39:35 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_and_start(t_element *data, t_philo **philos, int ac, char **av)
{
	data->forks = NULL;
	if (init_global_data(data, ac, av) != 0)
		return (ft_putstr_fd(2, "Error: Global initialization failed\n"), 1);
	*philos = init_philos(data);
	if (!*philos)
	{
		ft_putstr_fd(2, "Error: Philosophers initialization failed\n");
		return (clean_all(data, NULL), 1);
	}
	if (start_simulation(data, *philos) != 0)
	{
		ft_putstr_fd(2, "Error: Simulation failed\n");
		return (clean_all(data, *philos), 1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_element	data;
	t_philo		*philos;

	if (ac < 5 || ac > 6)
	{
		error_msg();
		return (1);
	}
	if (good_format(av) == 1)
		return (1);
	if (init_and_start(&data, &philos, ac, av) != 0)
		return (1);
	clean_all(&data, philos);
	return (0);
}
