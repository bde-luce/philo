/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:43:52 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/21 17:25:35 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		data;

	if (!check_args(argc, argv) || !init_data(argc, argv, &data))
		return (1);
	init_philo(&data);
	create_threads(&data);
	clean_all(&data);
}
