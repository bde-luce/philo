/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:04:18 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/21 18:00:26 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	initial_usleep(philo);
	if (philo->data->nbr_philos == 1)
		handle_one_philo(philo);
	pthread_mutex_lock(&philo->data->end_mutex);
	while (philo->data->end_flag == 0)
	{
		pthread_mutex_unlock(&philo->data->end_mutex);
		eating(philo);
		sleeping(philo);
		thinking(philo);
		pthread_mutex_lock(&philo->data->end_mutex);
	}
	pthread_mutex_unlock(&philo->data->end_mutex);
	return (NULL);
}

static int	check_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_lock(&data->philo[i].meal_mutex);
		if (get_current_time(data) - data->philo[i].time_last_meal
			>= data->time2die)
		{
			pthread_mutex_unlock(&data->philo[i].meal_mutex);
			print_log(&data->philo[i], data->philo[i].id, "died");
			return (1);
		}
		pthread_mutex_unlock(&data->philo[i].meal_mutex);
		i++;
	}
	return (0);
}

static int	check_full(t_data *data)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (data->nbr_meals != -1)
	{
		while (i < data->nbr_philos)
		{
			pthread_mutex_lock(&data->philo[i].meal_mutex);
			if (data->philo[i].meals_eaten >= data->nbr_meals)
				c++;
			pthread_mutex_unlock(&data->philo[i].meal_mutex);
			i++;
		}
		if (c == data->nbr_philos)
		{
			pthread_mutex_lock(&data->end_mutex);
			data->end_flag = 1;
			pthread_mutex_unlock(&data->end_mutex);
			return (1);
		}
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_dead(data) || check_full(data))
			break ;
		usleep(100);
	}
	return (NULL);
}
