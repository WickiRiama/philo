/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:15:14 by mriant            #+#    #+#             */
/*   Updated: 2022/05/19 15:20:44 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "philo_bonus.h"

int	ft_eat(t_philo *philos)
{
	ft_print_time(philos, "is eating");
	philos->last_eat = ft_gettime();
	philos->nb_meal++;
	ft_usleep(philos->args->time_eat, philos);
	if (philos->nb_meal == philos->args->nb_eat)
		sem_post(philos->args->sem_finished);
	sem_post(philos->args->sem_forks);
	sem_post(philos->args->sem_forks);
	return (0);
}

void	*ft_is_finished(void *philo_void)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)philo_void;
	while (i < philo->args->nb_philo)
	{
		sem_wait(philo->args->sem_finished);
		i++;
	}
	ft_children_kill(philo);
	return (NULL);
}

int	ft_take_fork(t_philo *philos)
{
	ft_usleep(0, philos);
	if (sem_wait(philos->args->sem_forks) == -1)
		ft_error("Waiting semaphore error", "");
	ft_usleep(0, philos);
	ft_print_time(philos, "has taken a fork");
	return (0);
}
