/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:37:26 by mriant            #+#    #+#             */
/*   Updated: 2022/04/19 16:25:10 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "philo.h"

void	*ft_philo(void *philos_void)
{
	t_philo	*philos;

	philos = (t_philo *) philos_void;
	if(philos->id % 2 == 0)
	usleep(20);
	while(1)
	{
	while(1)
	{
		pthread_mutex_lock(&philos->fork_mutex);
		if (philos->fork == 0)
		{
			philos->fork = 1;
			printf("%d has taken a fork\n", philos->id);
			break;
		}
		pthread_mutex_unlock(&philos->fork_mutex);
	}
	pthread_mutex_unlock(&philos->fork_mutex);
	while(1)
	{
		pthread_mutex_lock(&philos->prev->fork_mutex);
		if (philos->prev->fork == 0)
		{
			philos->prev->fork = 1;
			printf("%d has taken a fork\n", philos->id);
			break;
		}
		pthread_mutex_unlock(&philos->prev->fork_mutex);
	}
	pthread_mutex_unlock(&philos->prev->fork_mutex);
	printf("%d is eating\n", philos->id);
	usleep(philos->args->time_eat);
	pthread_mutex_lock(&philos->fork_mutex);
	philos->fork = 0;
	pthread_mutex_unlock(&philos->fork_mutex);
	pthread_mutex_lock(&philos->prev->fork_mutex);
	philos->prev->fork = 0;
	pthread_mutex_unlock(&philos->prev->fork_mutex);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_main		args;
	t_philo		*philos;
	t_philo		*temp;
	pthread_t	*tab;
	int			i;

	if (ac < 5 || ac > 6)
	{
		ft_error("nb_ac", NULL);
		return (1);
	}
	if (ft_parse(&args, ac, av) || ft_makelist(&philos, &args) 
		|| ft_init_time(&args, philos))
		return (1);
	tab = malloc(sizeof(pthread_t) * args.nb_philo);
	if (!tab)
	{
		ft_error("Malloc error ", "");
		free(args.tv);
		ft_lstclear(&philos);
		return (1);
	}
	i = 0;
	temp = philos;
	while (i < args.nb_philo)
	{
		if(pthread_create(&tab[i], NULL, &ft_philo, temp))
		{
			ft_error("Thread create error", "");
			free(args.tv);
			ft_lstclear(&philos);
			return (1);
		}
		temp = temp->next;
		i++;
	}
	i = 0;
	while (i < args.nb_philo)
	{
		pthread_join(tab[i], NULL);
		i++;
	}
	free(tab);
	free(args.tv);
	ft_lstclear(&philos);
	return (0);
}
