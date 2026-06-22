/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 15:32:53 by ragolden          #+#    #+#             */
/*   Updated: 2026/06/22 21:17:48 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long time_in_ms, t_element *data)
{
	long long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
	{
		pthread_mutex_lock(&data->dead_mut);
		if (data->dead_flag)
		{
			pthread_mutex_unlock(&data->dead_mut);
			break ;
		}
		pthread_mutex_unlock(&data->dead_mut);
		usleep(500);
	}
}
