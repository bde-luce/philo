/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:56:21 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/21 18:00:21 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	if (!print_log(philo, philo->id, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->first_fork);
		return ;
	}
	pthread_mutex_lock(philo->second_fork);
	if (!print_log(philo, philo->id, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return ;
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->time_last_meal = get_current_time(philo->data);
	pthread_mutex_unlock(&philo->meal_mutex);
	if (print_log(philo, philo->id, "is eating"))
	{
		pthread_mutex_lock(&philo->meal_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_mutex);
		usleep(philo->data->time2eat * 1000);
	}
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
}

void	sleeping(t_philo *philo)
{
	if (print_log(philo, philo->id, "is sleeping"))
		usleep(philo->data->time2sleep * 1000);
}

void	thinking(t_philo *philo)
{
	if (print_log(philo, philo->id, "is thinking"))
	{
		if (philo->data->nbr_philos % 2 != 0)
			usleep(philo->data->time2think * 1000);
	}
}

void	initial_usleep(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(philo->data->time2eat * 1000);
	if (philo->data->nbr_philos % 2 != 0 && philo->data->nbr_philos > 1
		&& philo->id == philo->data->nbr_philos)
		usleep(philo->data->time2eat * 2000);
}

void	handle_one_philo(t_philo *philo)
{
	printf("%lu %d has taken a fork\n", get_current_time(philo->data),
		philo->id);
	usleep(philo->data->time2die * 1000);
}
