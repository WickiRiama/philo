/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:16:13 by mriant            #+#    #+#             */
/*   Updated: 2022/05/18 16:52:41 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include "philo_bonus.h"

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

void	ft_clean(t_philo **philos, t_main *args, pid_t *tab)
{
	ft_lstclear(philos);
	sem_unlink("sem_fork");
	sem_unlink("sem_print");
	sem_unlink("sem_finished");
	sem_close(args->sem_forks);
	sem_close(args->sem_print);
	sem_close(args->sem_finished);
	free(tab);
}
