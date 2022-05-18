/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sources.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 23:16:32 by osallak           #+#    #+#             */
/*   Updated: 2022/05/16 11:42:48 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_list(t_info *infos, int id)
{
	t_philo	*node;

	node = malloc(sizeof(t_philo));
	if (!node)
	{
		printf("Cannot allocate memory\n");
		exit(1);
	}
	node->next = NULL;
	node->id = id;
	node->infos = infos;
	node->last_meal = infos->start_time;
	return (node);
}

void	add_back(t_philo **head, t_philo *new)
{
	t_philo	*tmp;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
