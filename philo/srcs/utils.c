/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 17:32:13 by mriant            #+#    #+#             */
/*   Updated: 2022/04/15 17:56:17 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	ft_error(char *str1, char *str2)
{
	if (ft_strcmp(str1, "nb_ac") == 0)
	{
		write(2, "Wrong number of arguments.\n"
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