/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:37:26 by mriant            #+#    #+#             */
/*   Updated: 2022/04/18 13:43:06 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

int	main(int ac, char **av)
{
	t_main	args;

	if (ac < 5 || ac > 6)
	{
		ft_error("nb_ac", NULL);
		return (1);
	}
	if (ft_parse(&args, ac, av) == 1)
		return (1);
	return (0);
}
