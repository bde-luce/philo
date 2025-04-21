/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:44:23 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/21 17:59:49 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h> 
# include <sys/time.h>
# include <unistd.h>

struct	s_data;

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

	unsigned long		time2think;
	unsigned long		start_time;
	int					end_flag;

	pthread_mutex_t		print_mutex;
	pthread_mutex_t		end_mutex;
	pthread_mutex_t		*fork;
	t_philo				*philo;
}	t_data;

// utils
unsigned int	unsigned_atoi(char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
unsigned long	get_time_elapsed(void);
unsigned long	get_current_time(t_data *data);
int				print_log(t_philo *philo, int id, char *message);

// check_args
int				args_in_range(t_data *data);
int				argv_positive_digit(char **argv);
int				check_args(int argc, char **argv);

// init
int				init_data(int argc, char **argv, t_data *data);
void			init_philo(t_data *data);

// routine_actions
void			eating(t_philo *philo);
void			sleeping(t_philo *philo);
void			thinking(t_philo *philo);
void			initial_usleep(t_philo *philo);
void			handle_one_philo(t_philo *philo);

// routine_control
void			*routine(void *arg);
void			*monitor_routine(void *arg);

// handle_threads
void			clean_all(t_data *data);
void			create_threads(t_data *data);

#endif