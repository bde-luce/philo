/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:44:23 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/17 18:19:50 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h> 
# include <sys/time.h>
# include <unistd.h>

struct s_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;

	unsigned long	time_last_meal;
	
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	pthread_mutex_t	meal_mutex;

	pthread_t		thread_id;

	struct s_data	*data;
	
}	t_philo;


typedef struct s_data
{
	int					nbr_philos;
	unsigned long		time2die;
	unsigned long		time2eat;
	unsigned long		time2sleep;
	int					nbr_meals;

	unsigned long		start_time;
	
	int					end_flag;

	pthread_mutex_t		print_mutex;
	
	pthread_mutex_t		end_mutex;
	
	pthread_mutex_t		*fork;
	
	t_philo				*philo;
	
}	t_data;

#endif