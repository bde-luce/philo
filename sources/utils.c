/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:53:07 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/21 17:59:42 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	unsigned_atoi(char *str)
{
	int		r;
	int		i;

	r = 0;
	i = 0;
	if (!str)
		return (0);
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		r = (r * 10) + (str[i] - 48);
		i++;
	}
	return (r);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && (s1[i] - s2[i]) == 0 && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

unsigned long	get_time_elapsed(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

unsigned long	get_current_time(t_data *data)
{
	return (get_time_elapsed() - data->start_time);
}

int	print_log(t_philo *philo, int id, char *message)
{
	unsigned long	time;

	time = get_current_time(philo->data);
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->end_mutex);
	if (philo->data->end_flag == 0)
	{
		if (ft_strncmp(message, "died", 5) == 0)
			philo->data->end_flag = 1;
		printf("%lu %d %s\n", time, id, message);
		pthread_mutex_unlock(&philo->data->end_mutex);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->end_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}
