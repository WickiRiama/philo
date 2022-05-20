/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:13:41 by mriant            #+#    #+#             */
/*   Updated: 2022/05/20 11:19:17 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

// # include <pthread.h>
// # include <sys/time.h>
# include <semaphore.h>

typedef struct s_main
{
	sem_t		*sem_forks;	
	sem_t		*sem_print;
	sem_t		*sem_finished;
	sem_t		*sem_all_finished;
	int			nb_eat;
	int			nb_philo;
	int			time_die;
	int			time_sleep;
	int			time_eat;
	long int	start_time;
}			t_main;
typedef struct s_philo
{
	int				id;
	int				fork;
	int				nb_meal;
	long int		last_eat;
	pid_t			pid;
	struct s_philo	*prev;
	struct s_philo	*next;
	t_main			*args;
}			t_philo;

int			ft_atoi_philo(char *str);
void		ft_children_kill(t_philo *philo);
void		ft_clean(t_philo **philos, t_main *args);
void			ft_eat(t_philo *philos);
void		ft_error(char *str1, char *str2);
long int	ft_gettime(void);
int			ft_init_all(t_main *args, t_philo **philos, int ac, char **av);
void		ft_init_time(t_main *args);
void		*ft_is_finished(void *philo);
void		ft_lstadd_back(t_philo **alst, t_philo *new);
void		ft_lstclear(t_philo **lst);
t_philo		*ft_lstnew(int id);
void		ft_print_time(t_philo *philo, char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strlen(char *str);
void		ft_take_fork(t_philo *philos);
void		ft_usleep(int sleep_time, t_philo *philo);

#endif