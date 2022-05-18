/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:15:14 by mriant            #+#    #+#             */
/*   Updated: 2022/05/18 16:58:13 by mriant           ###   ########.fr       */
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
	if (ft_print_time(philos, "is eating"))
		return (1);
	philos->last_eat = ft_gettime();
	philos->nb_meal++;
	if (ft_usleep(philos->args->time_eat, philos))
		return (1);
	if (philos->nb_meal == philos->args->nb_eat)
		philos->args->has_finished++;
	sem_post(philos->args->sem_forks);
	sem_post(philos->args->sem_forks);
	return (0);
}

int	ft_is_finished(t_philo *philo)
{
	if (philo->args->is_dead == 1)
		return (1);
	if (philo->args->has_finished == philo->args->nb_philo)
		return (1);
	return (0);
}

int	ft_take_fork(t_philo *philos)
{
	if (ft_usleep(0, philos))
		return (1);
	if (sem_wait(philos->args->sem_forks) == -1)
		ft_error("Waiting semaphore error", "");
	if (ft_usleep(0, philos))
		return (1);
	if (ft_print_time(philos, "has taken a fork"))
		return (1);
	return (0);
}
