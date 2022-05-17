/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:01:55 by mriant            #+#    #+#             */
/*   Updated: 2022/05/17 17:16:19 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
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

int	ft_children_init(pid_t *tab, t_main *args, t_philo *philos)
{
	int		i;
	t_philo	*temp;

	i = 0;
	temp = philos;
	ft_init_time(args);
	while (temp && i < args->nb_philo)
	{
		tab[i] = fork();
		if (tab[i] == -1)
		{
			ft_error("Child creating error", "");
			ft_clean(&philos, args, tab);
			return (1);
		}
		if (tab[i] == 0)
			ft_philo(philos);
		temp = temp->next;
		i++;
	}
	return (0);
}

void	ft_children_kill(t_main *args, pid_t *tab)
{
	int		i;
	pid_t	stopped_pid;

	stopped_pid = waitpid(-1, NULL, 0);
	if (stopped_pid == -1)
	{
		ft_error("Waiting children error", "");
		return ;
	}
	i = 0;
	while (i < args->nb_philo)
	{
		if (tab[i] != stopped_pid)
			if (kill(tab[i], SIGKILL) == -1)
				ft_error("Killimg children error", "");
		i++;
	}
	return ;
}

int	ft_children_dealer(t_philo *philos, t_main *args)
{
	pid_t	*tab;

	tab = malloc(sizeof(pid_t) * args->nb_philo);
	if (!tab)
	{
		ft_error("Malloc error ", "");
		ft_clean(&philos, args, tab);
		return (1);
	}
	if (ft_children_init(tab, args, philos))
		return (1);
	ft_children_kill(args, tab);
	free(tab);
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
	ft_clean(&philos, &args, NULL);
	return (0);
}
