/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:39:04 by mriant            #+#    #+#             */
/*   Updated: 2022/05/09 17:57:18 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

typedef struct s_main
{
	pthread_mutex_t	print_mutex;
	int				nb_eat;
	int				nb_philo;
	int				time_die;
	int				time_sleep;
	int				time_eat;
	struct timeval	*tv;
	long int		start_time;
}			t_main;
typedef struct s_philo
{
	pthread_mutex_t	fork_mutex;
	int				id;
	int				fork;
	long int		last_eat;
	struct s_philo	*prev;
	struct s_philo	*next;
	t_main			*args;
}			t_philo;

int		ft_atoi_philo(char *str);
void	ft_clean(t_philo **philos, t_main *args, pthread_t *tab);
void	ft_eat(t_philo *philos, struct timeval *tv);
void	ft_error(char *str1, char *str2);
int		ft_init_all(t_main *args, t_philo **philos, int ac, char **av);
void	ft_lstadd_back(t_philo **alst, t_philo *new);
void	ft_lstclear(t_philo **lst);
t_philo	*ft_lstnew(int id);
void	ft_print_time(t_philo *philo, char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(char *str);
void	ft_take_fork(t_philo *philos, int is_prev);

#endif