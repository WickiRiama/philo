/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 17:32:13 by mriant            #+#    #+#             */
/*   Updated: 2022/05/12 18:26:33 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i ++;
	return (s1[i] - s2[i]);
}

long int	ft_gettime(void)
{
	struct timeval	tv;
	long int		ms_time;

	gettimeofday(&tv, NULL);
	ms_time = (tv.tv_sec * 1000000 + tv.tv_usec) / 1000;
	return (ms_time);
}

int	ft_print_time(t_philo *philo, char *str)
{
	long int	ms_time;
	int			result;

	result = 0;
	pthread_mutex_lock(&philo->args->print_mutex);
	ms_time = ft_gettime() - philo->args->start_time;
	fprintf(stderr, "prinnt avant dead mutex\n");
	pthread_mutex_lock(&philo->args->dead_mutex);
	fprintf(stderr, "str to print %s\n", str);
	if (philo->args->is_dead == 1)
	{
		fprintf(stderr, "wrong if dead\n");
		pthread_mutex_unlock(&philo->args->dead_mutex);
		pthread_mutex_unlock(&philo->args->print_mutex);
		// fprintf(stderr, "fin dead\n");	
		return (1);
	}
	else if (ft_strcmp(str, "died") == 0)
	{
		fprintf(stderr, "good else dead\n");
		philo->args->is_dead = 1;
		result = 1;
	}
	pthread_mutex_unlock(&philo->args->dead_mutex);
	fprintf(stderr, "print avant finish mutex\n");
	pthread_mutex_lock(&philo->args->finish_mutex);
	if (philo->args->has_finished == philo->args->nb_philo)
	{
		pthread_mutex_unlock(&philo->args->finish_mutex);
		fprintf(stderr, "print fin finish\n");	
		pthread_mutex_unlock(&philo->args->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->finish_mutex);
	fprintf(stderr, "prnt apres finish mutex\n");
	// pthread_mutex_lock(&philo->args->print_mutex);
	printf("%ld %d %s\n", ms_time, philo->id, str);
	pthread_mutex_unlock(&philo->args->print_mutex);
	fprintf(stderr, "fin print %d\n", result);	
	return (result);
}

int	ft_usleep(int sleep_time, t_philo *philo)
{
	long int	cur_time;

	cur_time = ft_gettime();
	fprintf(stderr, "%ld %d start usleep\n", cur_time - philo->args->start_time, philo->id);
	if (cur_time + sleep_time - philo->last_eat > philo->args->time_die)
	{
		fprintf(stderr, "%d usleep dead, last eat : %ld, time die : %d, cur_time : %ld\n", philo->id, philo->last_eat, philo->args->time_die, cur_time);
		if (philo->last_eat + philo->args->time_die - cur_time > 0)
			usleep((philo->last_eat + philo->args->time_die - cur_time) * 1000);
		fprintf(stderr, "%d after usleep dead befor print\n", philo->id);
		ft_print_time(philo, "died");
		fprintf(stderr, "%d usleep dead after print\n", philo->id);
		return (1);
	}
	else
	{
		fprintf(stderr, "%d usleep ok\n", philo->id);
		usleep(sleep_time * 1000);
	}
	return (0);
}
