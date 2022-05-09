/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 17:32:13 by mriant            #+#    #+#             */
/*   Updated: 2022/05/09 18:03:23 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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

void	ft_print_time(t_philo *philo, char *str)
{
	long int	ms_time;

	pthread_mutex_lock(&philo->args->print_mutex);
	gettimeofday(philo->args->tv, NULL);
	ms_time = (philo->args->tv->tv_sec * 1000000 + philo->args->tv->tv_usec)
		/ 1000 - philo->args->start_time;
	printf("%ld %d %s\n", ms_time, philo->id, str);
	pthread_mutex_unlock(&philo->args->print_mutex);
}
