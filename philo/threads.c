#include "philo.h"

int philo_eat(t_philo *philo)
{
    t_data *data = philo->data;

    pthread_mutex_lock(&data->forks[philo->right_fork]);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(&data->forks[philo->left_fork]);
    print_status(philo, "has taken a fork");

    pthread_mutex_lock(&data->dead_lock);
    if (data->dead)
    {
        pthread_mutex_unlock(&data->dead_lock);
        pthread_mutex_unlock(&data->forks[philo->left_fork]);
        pthread_mutex_unlock(&data->forks[philo->right_fork]);
        return (1);
    }
    pthread_mutex_unlock(&data->dead_lock);

    print_status(philo, "is eating");
    philo->last_meal_time = get_time();
    smart_sleep(data->time_to_eat, data);
    philo->meals_eaten++;

    pthread_mutex_unlock(&data->forks[philo->left_fork]);
    pthread_mutex_unlock(&data->forks[philo->right_fork]);

    return (0);
}

int philo_sleep(t_philo *philo)
{
    // printf("enetering philo sleep\n");
    print_status(philo, "is sleeping");
    return (smart_sleep(philo->data->time_to_sleep, philo->data));
}

int philo_think(t_philo *philo)
{
    // printf("entering philo think\n");
    print_status(philo, "is thinking");
    return(0);
}

void one_philo(t_data *data)
{    
        print_status(&data->philos[0], "has taken a fork");
        smart_sleep(data->time_to_die, data);
        print_status(&data->philos[0], "died");
}