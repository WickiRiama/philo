/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:18:03 by mriant            #+#    #+#             */
/*   Updated: 2022/05/09 16:31:06 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

void	ft_eat(t_philo *philos, struct timeval *tv)
{
	ft_print_time(philos, "is eating");
	usleep(philos->args->time_eat * 1000);
	philos->last_eat = gettimeofday(tv, NULL);
	pthread_mutex_lock(&philos->fork_mutex);
	philos->fork = 0;
	pthread_mutex_unlock(&philos->fork_mutex);
	pthread_mutex_lock(&philos->prev->fork_mutex);
	philos->prev->fork = 0;
	pthread_mutex_unlock(&philos->prev->fork_mutex);
}

void	ft_take_fork(t_philo *philos, int is_prev)
{
	while (1)
	{
		pthread_mutex_lock(&philos->fork_mutex);
		if (philos->fork == 0)
		{
			philos->fork = 1;
			if (is_prev == 1)
				ft_print_time(philos, "has taken a fork");
			else
				ft_print_time(philos->next, "has taken a fork");
			pthread_mutex_unlock(&philos->fork_mutex);
			return ;
		}
		pthread_mutex_unlock(&philos->fork_mutex);
	}
}
