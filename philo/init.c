/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisimony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:09:33 by lisimony          #+#    #+#             */
/*   Updated: 2024/10/15 15:09:35 by lisimony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, t_philo *philos, pthread_mutex_t *forks,
		char **argv)
{
	int	num_philos;

	num_philos = ft_atol(argv[1]);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	data->dead_flag = 0;
	return (init_forks(forks, num_philos) && init_philos(philos, data, forks,
			argv));
}

int	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (1);
}

int	init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks,
		char **argv)
{
	int	i;
	int	num_philos;
	int	must_eat_count;

	num_philos = ft_atol(argv[1]);
	i = 0;
	while (i < num_philos)
	{
		philos[i].id = i + 1;
		philos[i].num_philos = num_philos;
		philos[i].time_to_die = ft_atol(argv[2]);
		philos[i].time_to_eat = ft_atol(argv[3]);
		philos[i].time_to_sleep = ft_atol(argv[4]);
		if (argv[5])
			must_eat_count = ft_atol(argv[5]);
		else
			must_eat_count = -1;
		philos[i].must_eat_count = must_eat_count;
		philos[i].last_meal = get_time();
		philos[i].start_time = get_time();
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].left_fork = &forks[i];
		if (i == 0)
			philos[i].right_fork = &forks[num_philos - 1];
		else
			philos[i].right_fork = &forks[i - 1];
		philos[i].meal_lock = &data->meal_lock;
		philos[i].write_lock = &data->write_lock;
		philos[i].dead_lock = &data->dead_lock;
		philos[i].dead = &data->dead_flag;
		i++;
	}
	return (1);
}
