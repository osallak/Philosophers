/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:24:31 by osallak           #+#    #+#             */
/*   Updated: 2022/05/20 10:41:32 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include<pthread.h>
# include<stdbool.h>
# include<sys/time.h>
# include<stdbool.h>
# define TAKEN_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"

typedef struct s_info
{
	size_t			start_time;
	int				number_of_philos;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				meals;
	pthread_mutex_t	*pen;
}	t_info;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	fork;
	t_info			*infos;
	pthread_t		thread;
	size_t			last_meal;
	int				meals;
	struct s_philo	*next;
}	t_philo;

size_t		get_time(void);
t_info		*parser(char **input, int ac);
t_philo		*init_list(t_info *infos, int id);
void		add_back(t_philo **head, t_philo *new);
void		ft_usleep(size_t ms, size_t curr_time);
void		check_death(t_philo *philos);
void		create_threads(t_philo *philos);
void		print_state(char *msg, int id, size_t ctime, pthread_mutex_t *pen);
void		*routine(void *arg);

#endif