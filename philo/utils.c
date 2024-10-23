/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisimony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:10:27 by lisimony          #+#    #+#             */
/*   Updated: 2024/10/15 15:10:28 by lisimony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (((*str == ' ') || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long milliseconds)
{
	long long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < milliseconds)
		usleep(100);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void    print_status(char *str, t_philo *philo, int id)
{
    long long    time;

    pthread_mutex_lock(philo->dead_lock);
    if (*philo->dead && str[0] != 'd')  // Check first letter instead of strcmp
    {
        pthread_mutex_unlock(philo->dead_lock);
        return;
    }
    pthread_mutex_unlock(philo->dead_lock);

    pthread_mutex_lock(philo->write_lock);
    time = get_time() - philo->start_time;
    printf("%lld %d %s\n", time, id, str);
    pthread_mutex_unlock(philo->write_lock);
}




int	philo_dead(t_philo *philo, long long time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	long long time_since_last_meal = get_time() - philo->last_meal;

	// Debugging to track last meal time vs time_to_die
	//printf("[DEBUG] Philosopher %d last meal time: %lld ms ago (time_to_die: %lld)\n",
		//philo->id, time_since_last_meal, time_to_die);

	if (time_since_last_meal >= time_to_die)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}
int check_philo_death(t_philo *philos, long long current_time)
{
    int i;
    long long time_since_last_meal;

    i = 0;
    while (i < philos[0].num_philos)
    {
        pthread_mutex_lock(philos[i].meal_lock);
        time_since_last_meal = current_time - philos[i].last_meal;
        if (!philos[i].eating && time_since_last_meal >= philos[i].time_to_die)
        {
            print_status("died", &philos[i], philos[i].id);
            pthread_mutex_lock(philos[i].dead_lock);
            *philos[i].dead = 1;
            pthread_mutex_unlock(philos[i].dead_lock);
            pthread_mutex_unlock(philos[i].meal_lock);
            return (1);
        }
        pthread_mutex_unlock(philos[i].meal_lock);
        i++;
    }
    return (0);
}



int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	if (philos[0].must_eat_count == -1)
		return (0);
	i = 0;
	finished_eating = 0;
	while (i < philos[0].num_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].must_eat_count)
			finished_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finished_eating == philos[0].num_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos[0].dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}
