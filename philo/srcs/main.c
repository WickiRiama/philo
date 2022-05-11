/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:37:26 by mriant            #+#    #+#             */
/*   Updated: 2022/05/09 18:28:37 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "philo.h"

void	*ft_philo(void *philos_void)
{
	t_philo			*philos;

	philos = (t_philo *) philos_void;
	philos->last_eat = philos->args->start_time;
	if (philos->id % 2 == 0)
		usleep((philos->args->time_eat * 500));
	while (1)
	{
		if (ft_take_fork(philos, 1))
			return (NULL);
		if (ft_take_fork(philos->prev, 2))
			return (NULL);
		if (ft_eat(philos))
			return (NULL);
		if (ft_died(philos))
			return (NULL);
		ft_print_time(philos, "is sleeping");
		if (ft_usleep(philos->args->time_sleep, philos))
			return (NULL);
		if (ft_died(philos))
			return (NULL);
		ft_print_time(philos, "is thinking");
	}
	return (NULL);
}

int	ft_threads_init(pthread_t *tab, t_main *args, t_philo *philos)
{
	int		i;
	t_philo	*temp;

	i = 0;
	temp = philos;
	ft_init_time(args);
	while (temp && i < args->nb_philo)
	{
		if (pthread_create(&tab[i], NULL, &ft_philo, temp))
		{
			ft_error("Thread creating error", "");
			ft_clean(&philos, args, tab);
			return (1);
		}
		temp = temp->next;
		i++;
	}
	return (0);
}

void	ft_threads_close(t_main *args, pthread_t *tab)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		pthread_join(tab[i], NULL);
		i++;
	}
	return ;
}

int	ft_threads_dealer(t_philo *philos, t_main *args)
{
	pthread_t	*tab;

	tab = malloc(sizeof(pthread_t) * args->nb_philo);
	if (!tab)
	{
		ft_error("Malloc error ", "");
		ft_clean(&philos, args, tab);
		return (1);
	}
	if (ft_threads_init(tab, args, philos))
		return (1);
	ft_threads_close(args, tab);
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
	if (ft_threads_dealer(philos, &args))
		return (1);
	ft_clean(&philos, &args, NULL);
	return (0);
}
