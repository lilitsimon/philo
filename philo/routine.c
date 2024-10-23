/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisimony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:10:07 by lisimony          #+#    #+#             */
/*   Updated: 2024/10/15 15:10:08 by lisimony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!philo_die_loop(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (ptr);
}

int	philo_die_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*monitor_routine(void *ptr)
{
	t_philo	*philos;

	philos = (t_philo *)ptr;
	while (!philo_die_loop(philos))
	{
		if (check_philo_death(philos) == 1 || check_if_all_ate(philos) == 1)
			break ;
		usleep(500);
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	pthread_t	observer;
	int			i;
	long long	start_time;

	i = 0;
	if (data->philos[0].num_philos == 1)
	{
		one_philo(data);
		return (0);
	}
	start_time = get_time();
	if (pthread_create(&observer, NULL, monitor_routine, data->philos) != 0)
		return (1);
	while (i < data->philos[0].num_philos)
	{
		data->philos[i].start_time = start_time;
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
			return (1);
		i++;
	}
	pthread_join(observer, NULL);
	i = 0;
	while (i < data->philos[0].num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}

void	one_philo(t_data *data)
{
	t_philo	*philo;

	philo = &data->philos[0];
	print_status("has taken a fork", philo, philo->id);
	ft_usleep(philo->time_to_die);
	print_status("died", philo, philo->id);
	pthread_mutex_lock(philo->dead_lock);
	*philo->dead = 1;
	pthread_mutex_unlock(philo->dead_lock);
}
