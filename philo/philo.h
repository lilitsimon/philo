
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
}		t_philo;

typedef struct s_args
{
}		t_args;

int		check_args(int argc, char **argv);
long	ft_atol(char *str);
int		is_number(char *str);

#endif