/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:17:30 by ragolden          #+#    #+#             */
/*   Updated: 2026/06/22 20:54:27 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_msg(void)
{
	ft_putstr_fd(2, "Invalid usage !\n");
	ft_putstr_fd(2, "Correct format:\n");
	ft_putstr_fd(2, "./philo <nb_of_philosophers> ");
	ft_putstr_fd(2, "<time_to_die> <time_to_eat> <time_to_sleep> ");
	ft_putstr_fd(2, "(optional) <nb_meals>\n");
}

int	good_format(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '+')
			j++;
		if (av[i][j] == '\0')
			return (1);
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				ft_putstr_fd(2, "Error: Arguments must be positive integers\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
