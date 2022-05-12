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

int	ft_eat(t_philo *philos)
{
	if (ft_print_time(philos, "is eating"))
		return (1);
	philos->last_eat = ft_gettime();
	if (ft_usleep(philos->args->time_eat, philos))
		return (1);
	pthread_mutex_lock(&philos->fork_mutex);
	philos->fork = 0;
	pthread_mutex_unlock(&philos->fork_mutex);
	pthread_mutex_lock(&philos->prev->fork_mutex);
	philos->prev->fork = 0;
	pthread_mutex_unlock(&philos->prev->fork_mutex);
	return (0);
}

int	ft_take_fork(t_philo *philos, int is_prev)
{
	t_philo	*cur_philo;

	if (is_prev == 2)
		cur_philo = philos->next;
	else
		cur_philo = philos;
	while (1)
	{
		ft_usleep(1, cur_philo);
		pthread_mutex_lock(&philos->fork_mutex);
		if (philos->fork == 0)
		{
			philos->fork = 1;
			pthread_mutex_unlock(&philos->fork_mutex);
			if (ft_print_time(cur_philo, "has taken a fork"))
				return (1);
			return (0);
		}
		pthread_mutex_unlock(&philos->fork_mutex);
	}
}
