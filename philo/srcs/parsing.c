/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:16:40 by mriant            #+#    #+#             */
/*   Updated: 2022/04/19 16:01:24 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

int	ft_parse(t_main *args, int ac, char **av)
{
	args->nb_eat = -2;
	if (ac == 6)
	{
		args->nb_eat = ft_atoi_philo(av[5]);
		if (args->nb_eat == -1)
			ft_error("Wrong argument ", av[5]);
	}
	args->nb_philo = ft_atoi_philo(av[1]);
	if (args->nb_philo == -1)
		ft_error("Wrong argument ", av[1]);
	args->time_die = ft_atoi_philo(av[2]);
	if (args->time_die == -1)
		ft_error("Wrong argument ", av[2]);
	args->time_eat = ft_atoi_philo(av[3]);
	if (args->time_eat == -1)
		ft_error("Wrong argument ", av[3]);
	args->time_sleep = ft_atoi_philo(av[4]);
	if (args->time_sleep == -1)
		ft_error("Wrong argument ", av[4]);
	if (args->nb_eat == -1 || args->nb_philo == -1 || args->time_die == -1
		|| args->time_eat == -1 || args->time_sleep == -1)
		return (1);
	return (0);
}

int	ft_makelist(t_philo **philos, t_main *args)
{
	int		i;
	t_philo	*new;

	i = 1;
	*philos = NULL;
	while (i < args->nb_philo + 1)
	{
		new = ft_lstnew(i);
		if (!new)
		{
			ft_error("Malloc error ", "");
			ft_lstclear(philos);
			return (1);
		}
		new->args = args;
		ft_lstadd_back(philos, new);
		i++;
	}
	return (0);
}

int	ft_init_time(t_main *args, t_philo *philos)
{
	args->tv = malloc(sizeof(struct timeval) * 1);
	if (!args->tv)
	{
		ft_error("Malloc error ", "");
		ft_lstclear(&philos);
		return (1);
	}
	gettimeofday(args->tv, NULL);
	args->start_time = (args->tv->tv_sec * 1000000 + args->tv->tv_usec) / 1000;
	return (0);
}
