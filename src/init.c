/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:55:08 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/21 17:58:13 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(int argc, char **argv, t_data *data)
{
	data->nbr_philos = unsigned_atoi(argv[1]);
	data->time2die = unsigned_atoi(argv[2]);
	data->time2eat = unsigned_atoi(argv[3]);
	data->time2sleep = unsigned_atoi(argv[4]);
	data->nbr_meals = 0;
	if (argc == 6)
		data->nbr_meals = unsigned_atoi(argv[5]);
	if (!args_in_range(data))
		return (0);
	if (argc == 5)
		data->nbr_meals = -1;
	data->time2think = 0.42 * (data->time2eat * 2 - data->time2sleep);
	data->philo = malloc(sizeof(t_philo) * data->nbr_philos);
	if (!data->philo)
		return (0);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nbr_philos);
	if (!data->fork)
		return (0);
	data->start_time = get_time_elapsed();
	data->end_flag = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->end_mutex, NULL);
	return (1);
}

static void	init_fork_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
}

static void	set_fork_order(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		if (data->philo[i].id % 2 != 0)
		{
			data->philo[i].first_fork = data->philo[i].l_fork;
			data->philo[i].second_fork = data->philo[i].r_fork;
		}
		else
		{
			data->philo[i].first_fork = data->philo[i].r_fork;
			data->philo[i].second_fork = data->philo[i].l_fork;
		}
		i++;
	}
}

void	init_philo(t_data *data)
{
	int				i;

	init_fork_mutex(data);
	i = 0;
	while (i < data->nbr_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals_eaten = 0;
		data->philo[i].time_last_meal = get_current_time(data);
		data->philo[i].r_fork = &data->fork[i];
		if (i < data->nbr_philos - 1)
			data->philo[i].l_fork = &data->fork[i + 1];
		else
			data->philo[i].l_fork = &data->fork[0];
		pthread_mutex_init(&data->philo[i].meal_mutex, NULL);
		data->philo[i].data = data;
		i++;
	}
	set_fork_order(data);
}
