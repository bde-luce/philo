/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:07:18 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/21 17:38:28 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_data *data)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_create(&data->philo[i].thread_id, NULL, routine,
			(void *)&data->philo[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, (void *)data);
	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_join(data->philo[i].thread_id, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

void	clean_all(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->end_mutex);
	while (i < data->nbr_philos)
	{
		pthread_mutex_destroy(&data->fork[i]);
		pthread_mutex_destroy(&data->philo[i].meal_mutex);
		i++;
	}
	free(data->fork);
	free(data->philo);
}
