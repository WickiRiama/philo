/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:01:55 by mriant            #+#    #+#             */
/*   Updated: 2022/05/19 13:22:30 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "philo_bonus.h"

void	*ft_philo(void *philos_void)
{
	t_philo			*philos;

	philos = (t_philo *) philos_void;
	philos->last_eat = philos->args->start_time;
	if (philos->id % 2 == 0)
		if (ft_usleep(philos->args->time_eat / 2, philos))
			exit(0);
	while (1)
	{
		if (ft_take_fork(philos))
			exit(0);
		if (ft_take_fork(philos))
			exit(0);
		if (ft_eat(philos))
			exit(0);
		if (ft_print_time(philos, "is sleeping"))
			exit(0);
		if (ft_usleep(philos->args->time_sleep, philos))
			exit(0);
		if (ft_print_time(philos, "is thinking"))
			exit(0);
	}
	exit(0);
}

int	ft_children_init(t_main *args, t_philo *philos)
{
	int		i;
	t_philo	*temp;

	i = 0;
	temp = philos;
	ft_init_time(args);
	while (temp && i < args->nb_philo)
	{
		args->tab[i] = fork();
		if (args->tab[i] == -1)
		{
			ft_error("Child creating error", "");
			ft_clean(&philos, args);
			return (1);
		}
		if (args->tab[i] == 0)
			ft_philo(temp);
		temp = temp->next;
		i++;
	}
	return (0);
}

void	ft_children_kill(t_main *args)
{
	int		i;

	i = 0;
	while (i < args->nb_philo)
	{
		if (kill(args->tab[i], SIGTERM) == -1)
			ft_error("Killing children error", "");
		i++;
	}
	return ;
}

int	ft_children_dealer(t_philo *philos, t_main *args)
{
	pthread_t	finish_pid;

	if (ft_children_init(args, philos))
		return (1);
	if (pthread_create(&finish_pid, NULL, &ft_is_finished, args))
	{
		ft_error("Thead creation error", "");
		ft_clean(&philos, args);
		return (1);
	}
	pthread_join(finish_pid, NULL);
	ft_children_kill(args);
	return (0);
}

int	main(int ac, char **av)
{
	t_main		args;
	t_philo		*philos;

	if (ac < 5 || ac > 6)
	{
		ft_error("nb_ac", NULL);
		return (1);
	}
	philos = NULL;
	if (ft_init_all(&args, &philos, ac, av))
		return (1);
	if (ft_children_dealer(philos, &args))
		return (1);
	ft_clean(&philos, &args);
	return (0);
}
