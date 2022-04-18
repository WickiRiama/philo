/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:39:04 by mriant            #+#    #+#             */
/*   Updated: 2022/04/18 13:54:24 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef struct s_main
{
	int	nb_eat;
	int	nb_philo;
	int	time_die;
	int	time_sleep;
	int	time_eat;
}			t_main;
typedef struct s_philo
{
	int		id;
	int		fork;
	struct s_philo *prev;
	struct s_philo *next;
	{
		/* data */
	};
	
}			t_philo;
{
	/* data */
};


int		ft_atoi_philo(char *str);
void	ft_error(char *str1, char *str2);
int		ft_parse(t_main *args, int ac, char **av);
int		ft_strlen(char *str);

#endif