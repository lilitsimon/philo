#include "philo.h"

void *philo_routine(void *arg)
{
    t_philo *philo;
    //t_data  *data;

    philo = (t_philo *)arg;
    //data = philo->data;

    if (philo->id % 2 == 0)
        usleep(1000); // delaying the even number philosophers /1milisecond, as this function takes 
    while (1)
    {
        if(philo_eat(philo)) // Checks if the philosopher can have forks to eat. // to implement;
            break;
        //if(philo_sleep(philo)) // Puts the philo to sleep// to implement;
            //break;
        //if(philo_think(philo)) // to implement;
            //break;
    }
    return (NULL);
}

int start_simulation(t_data *data)
{
    int i;
    //pthread_t monitor;

    i = 0;
    data->start_time = get_time();

    while (i < data->num_philos)
    {
        if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
            return (1);
        i++;
    }
        //if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
            //return(1);
    i = 0;
    while (i < data->num_philos)
    {
        if (pthread_join(data->philos[i].thread, NULL) != 0)
            return (1);
        i++;
    }
    //if (pthread_join(monitor, NULL) != 0)
        //return (1);
    return (0);
}

int philo_eat (t_philo *philo)
{
    t_data *data;

    data = philo->data;
    pthread_mutex_lock(&data->forks[philo->left_fork]);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(&data->forks[philo->right_fork]);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(&data->dead_lock);
    if (data->dead) //checking if the simulation has ended/someone died
    {
        pthread_mutex_lock(&data->dead_lock);
        pthread_mutex_unlock(&data->forks[philo->left_fork]);
        pthread_mutex_unlock(&data->forks[philo->right_fork]);
    }
    pthread_mutex_lock(&data->dead_lock);
    print_status(philo, "is eating");
    philo->last_meal_time = get_time();
    if (smart_sleep(data->time_to_eat, data))
        return (1);
    philo->meals_eaten++;
    pthread_mutex_unlock(&data->forks[philo->left_fork]);
    pthread_mutex_unlock(&data->forks[philo->right_fork]);
    return (0);
}





