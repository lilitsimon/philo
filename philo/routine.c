#include "philo.h"

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 0)
        usleep(1000);

    while (!dead_loop(philo))
    {
        if (philo_eat(philo))
            break;
        if (philo_sleep(philo))
            break;
        if (philo_think(philo))
            break;
    }
    return (NULL);
}

int dead_loop(t_philo *philo)
{
    t_data *data = philo->data;
    pthread_mutex_lock(&data->dead_lock);
    if (data->dead)
    {
        pthread_mutex_unlock(&data->dead_lock);
        return (1);
    }
    pthread_mutex_unlock(&data->dead_lock);
    return (0);
}

void *monitor_routine(void *arg)
{
    // printf("Entering monitor routine\n");
    t_data *data;
    int i;
    int finished;

    data = (t_data *)arg;
    while (1)
    {
        i = 0;
        finished = 0;
        while (i < data->num_philos)
        {
            if (check_philo_death(&data->philos[i]))
            {
                //printf("Monitor detected death, exiting\n");
                return NULL;
            }
            if (data->must_eat_count != -1 && data->philos[i].meals_eaten >= data->must_eat_count)
                finished++;
            i++;
        }
        if (finished == data->num_philos)
        {
            pthread_mutex_lock(&data->write_lock);
            // printf("All philosophers have eaten enough\n");
            pthread_mutex_unlock(&data->write_lock);
            pthread_mutex_lock(&data->dead_lock);
            data->dead = 1;
            pthread_mutex_unlock(&data->dead_lock);
            //printf("Monitor exiting due to meal completion\n");
            return NULL;
        }
        usleep(1000);  // just to reduce CPU usage
    }
}

int start_simulation(t_data *data)
{
    // printf("Starting simulation\n");
    int i;
    pthread_t monitor;

    data->start_time = get_time();

    if (data->num_philos == 1)
    {
        one_philo(data);
        return (0);
    }
    i = 0;
    while (i < data->num_philos)
    {
        if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
        {
            //printf("Error creating philosopher thread %d\n", i + 1);
            return (1);
        }
        i++;
    }
    if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
    {
        printf("Error creating monitor thread\n");
        return (1);
    }
    // Wait for monitor thread to finish
    // printf("Waiting for monitor thread to finish\n");
    if (pthread_join(monitor, NULL) != 0)
    {
        printf("Error joining monitor thread\n");
        return (1);
    }
    // printf("Monitor thread finished\n");
    pthread_mutex_lock(&data->dead_lock);
    data->dead = 1;
    pthread_mutex_unlock(&data->dead_lock);
    // printf("Waiting for philosopher threads to finish\n");
    i = 0;
    while (i < data->num_philos)
    {
        if (pthread_join(data->philos[i].thread, NULL) != 0)
        {
            // printf("Error joining philosopher thread %d\n", i + 1);
            return (1);
        }
        // printf("Philosopher thread %d joined\n", i + 1);
        i++;
    }
    // printf("All threads joined, simulation complete\n");
    return (0);
}








