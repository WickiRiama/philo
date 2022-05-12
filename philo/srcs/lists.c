/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:54:51 by mriant            #+#    #+#             */
/*   Updated: 2022/04/19 14:15:08 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

t_philo	*ft_lstnew(int id)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	if (pthread_mutex_init(&new->fork_mutex, NULL))
		return (NULL);
	new->id = id;
	new->fork = 0;
	new->nb_meal = 0;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int	ft_lstsize(t_philo *lst)
{
	int		i;
	t_philo	*first;

	if (!lst)
		return (0);
	i = 1;
	first = lst;
	while (lst->next && lst->next != first)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_philo	*ft_lstlast(t_philo *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next && lst->id < lst->next->id)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_philo **alst, t_philo *new)
{
	t_philo	*last;

	if (!(*alst))
	{
		*alst = new;
		new->next = new;
		new->prev = new;
	}
	else
	{
		last = ft_lstlast(*alst);
		last->next = new;
		new->prev = last;
		new->next = *alst;
		(*alst)->prev = new;
	}
}

void	ft_lstclear(t_philo **lst)
{
	t_philo	*temp1;
	t_philo	*temp2;
	int		i;
	int		size;

	temp2 = *lst;
	i = 0;
	size = ft_lstsize(*lst);
	while (i < size)
	{
		temp1 = temp2->next;
		pthread_mutex_destroy(&temp2->fork_mutex);
		free(temp2);
		temp2 = temp1;
		i++;
	}
	*lst = NULL;
}
