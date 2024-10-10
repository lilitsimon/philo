#include "philo.h"

long	ft_atol(char *str)
{
	long result;
	int sign;

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

int is_number(char *str)
{
    int i;
    i = 0;

    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }    
    return (1);
}

void print_status (t_philo *philo, char *status)
{
	t_data *data;
	long long current_time;

	data = philo->data;
	current_time = get_time() - data->start_time;
	pthread_mutex_lock(&data->write_lock);
	if (!data->dead)
		printf("%lld %d %s", current_time, philo->id, status);
	pthread_mutex_unlock(&data->write_lock);
}

int smart_sleep(long long milliseconds, t_data *data)
{
	long long start;
	long long current;

	start = get_time();
	current = get_time();
	while (1)
	{
		pthread_mutex_lock(&data->dead_lock);
			if (data->dead)
			{
				pthread_mutex_unlock(&data->dead_lock);
				return (1);
			}
		pthread_mutex_unlock(&data->dead_lock);
		current = get_time();
		if ((current - start) >= milliseconds)
			return (0);
		usleep (50); // Sleep for small intervals and check for the deaths regularly to end early, CPU usagy (more sleep, less usage, less responsive)
	}
}
