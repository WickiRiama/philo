/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:02:12 by mriant            #+#    #+#             */
/*   Updated: 2022/05/18 16:51:39 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "philo_bonus.h"

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
	while (i < args->nb_philo + 1)
	{
		new = ft_lstnew(i);
		if (!new)
		{
			ft_error("Malloc error ", "");
			return (1);
		}
		new->args = args;
		ft_lstadd_back(philos, new);
		i++;
	}
	return (0);
}

void	ft_init_time(t_main *args)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	args->start_time = ft_gettime();
	return ;
}

int	ft_init_semaphore(t_main *args)
{
	sem_unlink("sem_fork");
	sem_unlink("sem_print");
	sem_unlink("sem_finished");
	args->sem_forks = sem_open("sem_fork", O_CREAT, 0644, args->nb_philo);
	args->sem_print = sem_open("sem_print", O_CREAT, 0644, 1);
	args->sem_finished = sem_open("sem_finished", O_CREAT, 0644, 0);
	if (args->sem_forks == SEM_FAILED
		|| args->sem_print == SEM_FAILED
		|| args->sem_finished == SEM_FAILED)
	{
		printf("Semaphore error %s\n", strerror(errno));
		return (1);
	}
	return (0);
}

int	ft_init_all(t_main *args, t_philo **philos, int ac, char **av)
{
	args->nb_philo = 0;
	args->has_finished = 0;
	args->is_dead = 0;
	if (ft_parse(args, ac, av) || ft_makelist(philos, args))
	{
		ft_clean(philos, args, NULL);
		return (1);
	}
	if (ft_init_semaphore(args))
		return (1);
	return (0);
}
