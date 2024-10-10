
#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	long long		last_meal_time;
	struct s_data	*data;
	pthread_t		thread;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleap;
	int				must_eat_count;
	int				dead;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	t_philo			*philos;
}					t_data;

int					check_args(int argc, char **argv);
long				ft_atol(char *str);
int					is_number(char *str);
int					init_data(t_data *data, int argc, char **argv);
int					init_mutexes(t_data *data);
int					init_philos(t_data *data);
long long	get_time(void);
int start_simulation(t_data *data);
void *philo_routine(void *arg);
int philo_eat(t_philo *philo);
void print_status(t_philo *philo, char *status);
int smart_sleep(long long milliseconds, t_data *data);

#endif