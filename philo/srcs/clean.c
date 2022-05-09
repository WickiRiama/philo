/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:43:34 by mriant            #+#    #+#             */
/*   Updated: 2022/05/09 17:42:45 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "philo.h"

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

void	ft_clean(t_philo **philos, t_main *args, pthread_t *tab)
{
	ft_lstclear(philos);
	free(args->tv);
	pthread_mutex_destroy(&args->print_mutex);
	free(tab);
}
