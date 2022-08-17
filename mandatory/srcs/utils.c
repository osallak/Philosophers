/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:11:32 by osallak           #+#    #+#             */
/*   Updated: 2022/08/17 17:50:35 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	ft_usleep(size_t ms, size_t curr_time)
{
	usleep(ms * 0.95);
	while (get_time() < (curr_time + (ms / 1000)))
		usleep(100);
}

void	print_state(char *msg, int id, size_t start_time, pthread_mutex_t *pen)
{
	pthread_mutex_lock(pen);
	printf("%lu %d %s\n", get_time() - start_time, id, msg);
	pthread_mutex_unlock(pen);
}

void	free_allocated_memory(t_philo *philos)
{
	int		count;
	t_philo	*tmp;

	count = philos->infos->number_of_philos;
	free(philos->infos);
	while (count-- && philos)
	{
		tmp = philos;
		philos = philos->next;
		free(tmp);
	}
}

void	check_death(t_philo *philos)
{
	pthread_mutex_t	*pen;
	size_t			s_t;

	s_t = philos->infos->start_time;
	pen = philos->infos->pen;
	while (true)
	{
		if (get_time() - philos->last_meal > (size_t)philos->infos->time_to_die)
		{
			pthread_mutex_lock(pen);
			printf("%lu %d died\n", get_time() - s_t, philos->id);
			free_allocated_memory(philos);
			exit(0);
		}
		if (philos->id == philos->infos->number_of_philos
			&& philos->meals == philos->infos->meals)
		{
			free_allocated_memory(philos);
			exit(0);
		}
		philos = philos->next;
	}
}

void	create_threads(t_philo *philos)
{
	t_philo	*tmp;

	tmp = philos;
	philos->infos->pen = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philos->infos->pen, NULL);
	while (philos)
	{
		philos->meals = 0;
		if (!philos->next)
		{
			philos->next = tmp;
			pthread_create(&philos->thread, NULL, routine, philos);
			break ;
		}
		pthread_create(&philos->thread, NULL, routine, philos);
		philos = philos->next;
	}
}
