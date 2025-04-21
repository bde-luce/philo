/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:54:35 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/21 17:48:44 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	args_in_range(t_data *data)
{
	if (data->nbr_philos <= 0 || data->nbr_philos > 2147483647)
		printf("Error: Number of philosophers has to be a positive number "
			"lower than INT_MAX\n");
	else if (data->time2die < 60 || data->time2die > 2147483647 
		|| data->time2eat < 60 || data->time2eat > 2147483647 
		|| data->time2sleep < 60 || data->time2sleep > 2147483647)
		printf("Error: Use timestamps bigger than 60ms and less that INT_MAX\n");
	else if (data->nbr_meals < 0 || data->nbr_meals > 2147483647)
		printf("Error: Number of meals has to be a positive number lower than "
			"INT_MAX\n");
	else
		return (1);
	return (0);
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
				printf("Wrong type of argument: must be positive sequence of "
					"digits\n");
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
