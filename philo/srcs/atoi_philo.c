/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 17:32:05 by mriant            #+#    #+#             */
/*   Updated: 2022/05/20 14:03:33 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

int	ft_isspace(char c)
{
	if ((c == 32) || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

int	ft_atoi_philo(char *str)
{
	long int	n;
	int			i;

	if (!str)
		return (-1);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (-1);
	if (str[i] == '\0')
		return (-1);
	n = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (-1);
		n = n * 10 + str[i] - '0';
		i++;
	}
	return ((int)n);
}

void	ft_putnbr_philo(long int n)
{
	char	c;

	if (n / 10 != 0)
		ft_putnbr_philo(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}
