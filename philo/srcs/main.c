/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:37:26 by mriant            #+#    #+#             */
/*   Updated: 2022/04/19 13:15:23 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

int	main(int ac, char **av)
{
	t_main	args;
	t_philo	*philos;

	if (ac < 5 || ac > 6)
	{
		ft_error("nb_ac", NULL);
		return (1);
	}
	if (ft_parse(&args, ac, av) || ft_makelist(&philos, args.nb_philo))
		return (1);
	ft_lstclear(&philos);
	return (0);
}
