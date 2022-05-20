/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:19:12 by osallak           #+#    #+#             */
/*   Updated: 2022/05/20 10:47:39 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

static void	take_forks(t_philo *philos)
{
	pthread_mutex_t	*pen;

	pen = philos->infos->pen;
	if ((philos->id % 2))
	{
		pthread_mutex_lock(&philos->fork);
		print_state(TAKEN_FORK, philos->id, philos->infos->start_time, pen);
		pthread_mutex_lock(&philos->next->fork);
		print_state(TAKEN_FORK, philos->id, philos->infos->start_time, pen);
	}
	else
	{
		ft_usleep(2, get_time());
		pthread_mutex_lock(&philos->next->fork);
		print_state(TAKEN_FORK, philos->id, philos->infos->start_time, pen);
		pthread_mutex_lock(&philos->fork);
		print_state(TAKEN_FORK, philos->id, philos->infos->start_time, pen);
	}
}

static void	put_forks(t_philo *philos)
{
	if ((philos->id % 2))
	{
		pthread_mutex_unlock(&philos->fork);
		pthread_mutex_unlock(&philos->next->fork);
	}
	else
	{
		pthread_mutex_unlock(&philos->next->fork);
		pthread_mutex_unlock(&philos->fork);
	}
}

void	*routine(void *arg)
{
	t_philo			*philos;
	pthread_mutex_t	*pen;

	philos = (t_philo *) arg;
	pen = philos->infos->pen;
	philos->last_meal = philos->infos->start_time;
	philos->meals = 0;
	while (true)
	{
		take_forks(philos);
		print_state(EATING, philos->id, philos->infos->start_time, pen);
		philos->meals++;
		philos->last_meal = get_time();
		ft_usleep(philos->infos->time_to_eat * 1000, get_time());
		put_forks(philos);
		print_state(SLEEPING, philos->id, philos->infos->start_time, pen);
		ft_usleep(philos->infos->time_to_sleep * 1000, get_time());
		print_state(THINKING, philos->id, philos->infos->start_time, pen);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_info			*infos;
	t_philo			*philos;
	t_philo			*tmp;
	int				i;

	infos = parser(av, ac);
	i = 0;
	philos = NULL;
	while (i < infos->number_of_philos)
	{
		tmp = init_list(infos, i + 1);
		add_back(&philos, tmp);
		pthread_mutex_init(&tmp->fork, NULL);
		i++;
	}
	create_threads(philos);
	check_death(philos);
}
