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
	if (ft_died(philos))
		return (1);
	ft_print_time(philos, "is eating");
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

	cur_philo = philos;
	if (is_prev == 2)
		cur_philo = philos->next;
	while (1)
	{
		if (ft_died(cur_philo))
			return (1);
		pthread_mutex_lock(&philos->fork_mutex);
		if (philos->fork == 0)
		{
			philos->fork = 1;
			ft_print_time(cur_philo, "has taken a fork");
			pthread_mutex_unlock(&philos->fork_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philos->fork_mutex);
	}
}

int	ft_died(t_philo *philo)
{
	long int	cur_time;

	cur_time = ft_gettime();
	pthread_mutex_lock(&philo->args->dead_mutex);
	if (philo->args->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->args->dead_mutex);
		return (1);
	}
	if (cur_time - philo->last_eat > philo->args->time_die)
	{
		philo->args->is_dead = 1;
		ft_print_time(philo, "died");
		pthread_mutex_unlock(&philo->args->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->dead_mutex);
	return (0);
}
