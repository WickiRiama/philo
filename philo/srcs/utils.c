/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 17:32:13 by mriant            #+#    #+#             */
/*   Updated: 2022/04/19 14:16:22 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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

void	ft_error(char *str1, char *str2)
{
	write(2, "Error: ", 7);
	if (ft_strcmp(str1, "nb_ac") == 0)
	{
		write(2, "Wrong number of arguments\n"
			"./philo number_of_philosophers time_to_die"
			" time_to_eat time_to_sleep"
			" [number_of_times_each_philosopher_must_eat]\n", 140);
	}
	else
	{
		write(2, str1, ft_strlen(str1));
		write(2, str2, ft_strlen(str2));
		write(2, "\n", 1);
	}
}

void	ft_print_time(t_main args)
{
	gettimeofday(args.tv, NULL);
	printf("%ld\n", (args.tv->tv_sec * 1000000 + args.tv->tv_usec)
		/ 1000 - args.start_time);
}
