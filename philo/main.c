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

void	cleanup(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->philos[0].num_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data			data;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int				num_philos;

	if (!check_args(argc, argv))
		return (1);
	num_philos = ft_atol(argv[1]);
	forks = malloc(sizeof(pthread_mutex_t) * num_philos);
	philos = malloc(sizeof(t_philo) * num_philos);
	if (!forks || !philos)
		return (printf("Error: Memory allocation failed\n"), 1);
	data.philos = philos;
	if (!init_data(&data, philos, forks, argv))
	{
		cleanup(&data, forks);
		free(forks);
		return (1);
	}
	if (start_simulation(&data) != 0)
	{
		cleanup(&data, forks);
		free(forks);
		return (1);
	}
	cleanup(&data, forks);
	free(forks);
	return (0);
}
