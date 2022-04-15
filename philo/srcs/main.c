/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:37:26 by mriant            #+#    #+#             */
/*   Updated: 2022/04/15 17:58:15 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

int	main(int ac, char **av)
{
	t_main	args;

	if (ac < 5 || ac > 6)
	{
		ft_error("nb_ac", NULL);
		return (1);
	}
	args.nb_eat = -1;
	if (ac == 6)
	{
		args.nb_eat = ft_atoi_philo(av[5]);
		if (args.nb_eat == -1)
		{
			ft_error("Wrong argument ", av[5]);
			return (1);
		}
	}
	args.nb_philo = ft_atoi_philo(av[1]);
	args.time_die = ft_atoi_philo(av[2]);
	args.time_eat = ft_atoi_philo(av[3]);
	args.time_sleep = ft_atoi_philo(av[4]);
	return (0);
}
