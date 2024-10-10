#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleap = ft_atol(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atol(argv[5]);
	else
		data->must_eat_count = -1;
	data->dead = 0;
	data->start_time = get_time();
	return (init_mutexes(data) && init_philos(data));
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (0);
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
		i++;
		if (pthread_mutex_init(&data->write_lock, NULL) != 0)
			return (0);
		if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
			return (0);
	}
	return (1);
}

int	init_philos(t_data *data)
{
	int i;

	i = 0;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (0);
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philos;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].data = data;
        i++;
	}
    return (1);
}

long long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}