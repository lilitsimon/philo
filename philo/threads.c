/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisimony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:10:13 by lisimony          #+#    #+#             */
/*   Updated: 2024/10/15 15:10:22 by lisimony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        print_status("has taken a fork", philo, philo->id);
        pthread_mutex_lock(philo->right_fork);
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        print_status("has taken a fork", philo, philo->id);
        pthread_mutex_lock(philo->left_fork);
    }

    print_status("is eating", philo, philo->id);
    pthread_mutex_lock(philo->meal_lock);
    philo->last_meal = get_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->meal_lock);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    
    ft_usleep(philo->time_to_eat);
}





void	philo_sleep(t_philo *philo)
{
	print_status("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}


void	philo_think(t_philo *philo)
{
	print_status("is thinking", philo, philo->id);
}
