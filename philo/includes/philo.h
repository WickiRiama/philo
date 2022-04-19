/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:39:04 by mriant            #+#    #+#             */
/*   Updated: 2022/04/19 13:14:29 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

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
	pthread_mutex_t fork_mutex;
	int		id;
	int		fork;
	struct s_philo *prev;
	struct s_philo *next;
}			t_philo;

int		ft_atoi_philo(char *str);
void	ft_error(char *str1, char *str2);
void	ft_lstadd_back(t_philo **alst, t_philo *new);
void	ft_lstclear(t_philo **lst);
t_philo	*ft_lstnew(int id);
int		ft_makelist(t_philo **philos, int nb_philos);
int		ft_parse(t_main *args, int ac, char **av);
int		ft_strlen(char *str);

#endif