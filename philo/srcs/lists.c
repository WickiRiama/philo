/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:54:51 by mriant            #+#    #+#             */
/*   Updated: 2022/04/18 15:55:26 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_lstnew(int id)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->id = id;
	new->fork = 0;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int	ft_lstsize(t_philo *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (i);
	while (lst)
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
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_philo **alst, t_philo *new)
{
	t_philo	*last;

	if (!(*alst))
		*alst = new;
	else
	{
		last = ft_lstlast(*alst);
		last->next = new;
		new->prev = last;
	}
}

void	ft_lstdelone(t_philo *lst, void (*del)(void *))
{
	if (del)
		del(lst->content);
	if (lst->prev)
		lst->prev->next = NULL;
	free(lst);
}

void	ft_lstclear(t_philo **lst, void (*del)(void *))
{
	t_philo	*temp1;
	t_philo	*temp2;

	temp2 = *lst;
	while (temp2)
	{
		temp1 = temp2->next;
		ft_lstdelone(temp2, del);
		temp2 = temp1;
	}
	*lst = NULL;
}