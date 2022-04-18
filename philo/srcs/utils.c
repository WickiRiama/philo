/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 17:32:13 by mriant            #+#    #+#             */
/*   Updated: 2022/04/18 13:44:17 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_parse(t_main *args, int ac, char **av)
{
	args->nb_eat = -2;
	if (ac == 6)
	{
		args->nb_eat = ft_atoi_philo(av[5]);
		if (args->nb_eat == -1)
			ft_error("Wrong argument ", av[5]);
	}
	args->nb_philo = ft_atoi_philo(av[1]);
	if (args->nb_philo == -1)
		ft_error("Wrong argument ", av[1]);
	args->time_die = ft_atoi_philo(av[2]);
	if (args->time_die == -1)
		ft_error("Wrong argument ", av[2]);
	args->time_eat = ft_atoi_philo(av[3]);
	if (args->time_eat == -1)
		ft_error("Wrong argument ", av[3]);
	args->time_sleep = ft_atoi_philo(av[4]);
	if (args->time_sleep == -1)
		ft_error("Wrong argument ", av[4]);
	if (args->nb_eat == -1 || args->nb_philo == -1 || args->time_die == -1
		|| args->time_eat == -1 || args->time_sleep == -1)
		return (1);
	return (0);
}
