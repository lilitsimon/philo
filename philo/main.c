/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisimony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:09:21 by lisimony          #+#    #+#             */
/*   Updated: 2024/10/15 15:09:25 by lisimony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int		i;
	long	value;

	if (argc < 5 || argc > 6)
		return (printf("Error: Wrong number of arguments\n"), 0);
	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
			return (printf("Error: Invalid argument: %s\n", argv[i]), 0);
		value = ft_atol(argv[i]);
		if (value <= 0 || value > LONG_MAX)
			return (printf("Error: Invalid argument value: %s\n", argv[i]), 0);
		i++;
	}
	if (ft_atol(argv[1]) > 200)
		return (printf("Error: Invalid number of philosophers (max 200)\n"), 0);
	return (1);
}

void cleanup(t_data *data)
{
	int i;

	i = 0;

	if (data->forks)
	{
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);

	if (data->philos)
		free(data->philos);
}


int	main(int argc, char **argv)
{
    t_data data;
	if (!check_args(argc, argv))
	{
		printf("Input validation failed\n");
		return (1);
	}
	// printf("initialing data\n");
    if(!init_data(&data, argc, argv))
    { 
        printf("Error: Initialization failed\n");
        cleanup(&data);
        return (1);
    }
	// printf("starting simulation\n");
    if (start_simulation(&data)!= 0)
	{
		printf("Error: Simulation failed)");
		cleanup(&data);
		return (1);
	}
	// printf("simulation finished ok");
   	cleanup(&data);
    return (0);
}
