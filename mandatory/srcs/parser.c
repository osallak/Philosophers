/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:45:50 by osallak           #+#    #+#             */
/*   Updated: 2022/05/18 14:07:03 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

bool	check_errors(char **input)
{
	int		i;
	int		j;
	char	c;

	i = 1;
	while (input[i])
	{
		j = 0;
		while (input[i][j])
		{
			c = input[i][j];
			if (!ft_isdigit(c) && c != '+')
				return (false);
			if ((c == '+' && !ft_isdigit(input[i][j + 1]))
				|| (ft_isdigit(c)
				&& (input[i][j+1] && !ft_isdigit(input[i][j + 1]))))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

size_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

t_info	*parser(char **input, int ac)
{
	t_info	*infos;

	if (ac <= 4 || !check_errors(input))
	{
		printf("Error\n");
		exit(0);
	}
	infos = (t_info *)malloc(sizeof(t_info));
	if (!infos)
	{
		printf("Cannot allocate memory\n");
		exit(1);
	}
	infos->number_of_philos = atoi(input[1]);
	infos->time_to_die = atoi(input[2]);
	infos->time_to_eat = atoi(input[3]);
	infos->time_to_sleep = atoi(input[4]);
	if (ac == 6)
		infos->meals = atoi(input[5]);
	else
		infos->meals = -1;
	infos->start_time = get_time();
	return (infos);
}
