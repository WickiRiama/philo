/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:18:03 by mriant            #+#    #+#             */
/*   Updated: 2022/05/20 12:27:39 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo *philos)
{
	if (ft_print_time(philos, " is eating\n"))
		return (1);
	philos->last_eat = ft_gettime();
	philos->nb_meal++;
	if (ft_usleep(philos->args->time_eat, philos))
		return (1);
	if (philos->nb_meal == philos->args->nb_eat)
	{
		pthread_mutex_lock(&philos->args->finish_mutex);
		philos->args->has_finished++;
		pthread_mutex_unlock(&philos->args->finish_mutex);
	}
	pthread_mutex_lock(&philos->fork_mutex);
	philos->fork = 0;
	pthread_mutex_unlock(&philos->fork_mutex);
	pthread_mutex_lock(&philos->prev->fork_mutex);
	philos->prev->fork = 0;
	pthread_mutex_unlock(&philos->prev->fork_mutex);
	return (0);
}

int	ft_is_finished(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->dead_mutex);
	if (philo->args->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->args->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->dead_mutex);
	pthread_mutex_lock(&philo->args->finish_mutex);
	if (philo->args->has_finished == philo->args->nb_philo)
	{
		pthread_mutex_unlock(&philo->args->finish_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->finish_mutex);
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
		if (ft_usleep(0, cur_philo))
			return (1);
		pthread_mutex_lock(&philos->fork_mutex);
		if (philos->fork == 0)
		{
			philos->fork = 1;
			pthread_mutex_unlock(&philos->fork_mutex);
			if (ft_print_time(cur_philo, " has taken a fork\n"))
				return (1);
			return (0);
		}
		pthread_mutex_unlock(&philos->fork_mutex);
	}
}
