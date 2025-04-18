/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:43:52 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/18 16:26:23 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	unsigned_atoi(char *str)
{
	int	r;
	int		i;

	r = 0;
	i = 0;
	if (!str)
		return (0);
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		r = (r * 10)  + (str[i] - 48);
		i++;
	}
	return (r);
}

int	ph_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && (s1[i] - s2[i]) == 0 && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	args_in_range(t_data *data)
{
	if (data->nbr_philos <= 0 || data->nbr_philos > 2147483647)
		printf("Error: Number of philosophers has to be a positive number lower than INT_MAX\n");
	else if (data->time2die < 60 || data->time2die > 2147483647 
		|| data->time2eat < 60 || data->time2eat > 2147483647 
		|| data->time2sleep < 60 || data->time2sleep > 2147483647)
		printf("Error: Use timestamps bigger than 60ms and less that INT_MAX\n");
	else if (data->nbr_meals < 0 || data->nbr_meals > 2147483647)
		printf("Error: Number of meals has to be a positive number lower than INT_MAX\n");
	else
		return (1);
	return (0);
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

int	argv_positive_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv && argv[i])
	{
		j = 0;
		if (argv[i][j] == '+' && argv[i][j + 1])
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Wrong type of argument: must be positive sequence of digits\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("wrong amount of arguments\n");
		return (0);
	}
	if (!argv_positive_digit(argv))
		return (0);
	return (1);
}

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

void	set_fork_order(t_data *data)
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

void	init_fork_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
}

void	init_philo(t_data *data)
{
	int				i;

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

unsigned long	get_elapsed_microseconds(struct timeval start, struct timeval current)
{
	return ((current.tv_sec - start.tv_sec) * 1000000L + (current.tv_usec - start.tv_usec));
}

void	precise_usleep(unsigned long time)
{
	struct timeval	start;
	struct timeval	current;
	unsigned long	elapsed;
	unsigned long	rem;

	gettimeofday(&start, NULL);
	elapsed = 0;
	rem = time;
	while (elapsed < (time * 1000L))
	{
		gettimeofday(&current, NULL);
		elapsed = get_elapsed_microseconds(start, current);
		rem = (time * 1000L) - elapsed;
		if (rem > 1000)	
			usleep(rem / 2); 
	}
}

int	printf_message(t_philo *philo, unsigned long time, int id, char *message)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->end_mutex);
	if (philo->data->end_flag == 0)
	{
		if (ph_strncmp(message, "died", 5) == 0)
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

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	if (!printf_message(philo, get_current_time(philo->data), philo->id, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->first_fork);
		return ;
	}
	pthread_mutex_lock(philo->second_fork);
	if (!printf_message(philo, get_current_time(philo->data), philo->id, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return ;
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->time_last_meal = get_current_time(philo->data);
	pthread_mutex_unlock(&philo->meal_mutex);
	if (printf_message(philo, philo->time_last_meal, philo->id, "is eating"))
	{
		pthread_mutex_lock(&philo->meal_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_mutex);
		precise_usleep(philo->data->time2eat);
	}
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
}

void	sleeping(t_philo *philo)
{
	if (printf_message(philo, get_current_time(philo->data), philo->id, "is sleeping"))
		precise_usleep(philo->data->time2sleep);
}

void	thinking(t_philo *philo)
{
	printf_message(philo, get_current_time(philo->data), philo->id, "is thinking");
}

// void	initial_usleep(t_philo *philo)
// {
// 	if (philo->data->nbr_philos % 2 == 0)
// 	{
// 		if (philo->id % 2 == 0)
// 			precise_usleep(philo->data->time2eat);
// 	}
// 	else
// 	{
// 		if (philo->id == philo->data->nbr_philos)
// 			precise_usleep(philo->data->time2eat * 2);
// 		else if (philo->id % 2 == 0)
// 			precise_usleep(philo->data->time2eat);
// 	}
// }

void	initial_usleep(t_philo *philo)
{
	if (philo->id % 2 == 0)
		precise_usleep(philo->data->time2eat);
	if (philo->data->nbr_philos % 2 != 0 && philo->data->nbr_philos > 1 && philo->id == philo->data->nbr_philos)
		precise_usleep(philo->data->time2eat * 2);
}

void	handle_one_philo(t_philo *philo)
{
	printf("%lu %d has taken a fork\n", get_current_time(philo->data), philo->id);
	precise_usleep(philo->data->time2die);
}

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

int	check_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_lock(&data->philo[i].meal_mutex);
		if (get_current_time(data) - data->philo[i].time_last_meal >= data->time2die)
		{
			pthread_mutex_unlock(&data->philo[i].meal_mutex);
			printf_message(&data->philo[i], get_current_time(data), data->philo[i].id, "died");
			return (1);
		}
		pthread_mutex_unlock(&data->philo[i].meal_mutex);
		i++;
	}
	return (0);
}

int	check_full(t_data *data)
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
			break;
		usleep(100);
	}
	return (NULL);
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

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;
	int			i;
	if (!check_args(argc, argv) || !init_data(argc, argv, &data))
		return (1);
	init_fork_mutex(&data);
	init_philo(&data);
	i = 0;
	while (i < data.nbr_philos)
	{
		pthread_create(&data.philo[i].thread_id, NULL, routine, (void *)&data.philo[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, (void *)&data);
	i = 0;
	while (i < data.nbr_philos)
	{
		pthread_join(data.philo[i].thread_id, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	clean_all(&data);
}
